#include "Block.h"
#include "Square.h"
#include "Board.h"
#include <utility>

using namespace std;

//default constructor
//check for valid grid assignment in superclass constructor
//throws std::bad_alloc exception is the new block cannot fit onto the grid
Block::Block(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Board *bd, int level, char type, int colour) {
	//if the configurations are not valid, throw bad_alloc exception
	if (!validBlock(x1, y1, x2, y2, x3, y3, x4, y4)) {
		throw std::bad_alloc();
	}
	//configuration is valid
	else {
		Xwindow* xw = bd->getMainWindow();
		cout << "Setting xw="<<xw<<endl;
		numSquares = 4;
		//create the squares
		squares[0] = new Square(x1,y1,this,xw,type);  //NULL Xwindow b/c we are not displaying the squres in Block
		squares[1] = new Square(x2,y2,this,xw,type);
		squares[2] = new Square(x3,y3,this,xw,type);
		squares[3] = new Square(x4,y4,this,xw,type);

		//default orientation is up
		orientation(up);
	}
	this->colour = colour;
	this->type = type;
	this->bdp = bd;
	cout << "BDP=:"<<bdp<<" is set"<<endl;
	this->level = level;
}

Block::~Block() {
   cout << "block's destructor" << endl;
   //delete any remaining squares
   for (int c = 0; c< numSquares; c++) {
   cout << numSquares << " # of squares left in Block" << endl;
      delete squares[c];
   }
}

bool Block::validBlock(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	return true;
}

//checks to see if a move of i positions horizontally and j positions vertically is valid before moving the block
//return true if the move is valid, false otherwise
bool Block::validMove(int x, int y) {
	//iterative over each square to check if the move is valid
	for (int c = 0; c< numSquares; c++) {
		Square * currentSquare = squares[c];
		cout << "trying to move" << endl;
		if (!bdp->validMove(currentSquare,x,y)) {
			return false;
		}
	}
	//move is valid so return true
	cout << "Valid move" << endl;
	return true;

}
//drops the block down 1 row
//return true if the drop is successful. Returns false if the drop is not allowed (and nothing is changed)
bool Block::drop() {
	//check if the move is valid before moving the block
	if (!validMove(0,1)) return false;

	//drop is valid, so move squares down by 1 row

	//Move the squares that are on the bottom first
	int minx = getminx();
	int miny = getminy();
	int maxx = getmaxx();
	int maxy = getmaxy();
	for (int x = maxx; x >= minx; x--) {
		for (int y = maxy; y >= miny; y--) {
			for (int c = 0; c < numSquares; c++) {
				Square * cs = squares[c];
				//if the current co-ordinates actually correspond to a square, then move it
				if (cs->x == x && cs->y == y) {
					bdp->moveSquare(cs,0,1);
				}
			}
		}
	}
	return true;
}

//drops the block down until the bottom
//return true if the drop is successful. Returns false if the drop is not allowed (and nothing is changed)
void Block::dropdown() {
	//keep dropping if possible
	/*
	while (validMove(0,1)) {
		//drop is valid, so move squares down by 1 row
		for (int c = 0; c< numSquares; c++) {
			Square * currentSquare = squares[c];
			bdp->moveSquare(currentSquare,0,1);
		}
	}
	*/
	while (drop()) {}

	//once dropped to the bottom, call Board's Update method for new iteration
	bdp->Update();
}

//shifts the block to the right by 1 column
//return true if the shift is successful. Returns false if the shift is not allowed (and nothing is changed)
bool Block::shiftRight() {
	//check if the move is valid before moving the block
	if (!validMove(1,0)) return false;

	//shift is valid, so move squares right by 1 column

	//Move the squares that are on the righthand first
	int minx = getminx();
	int miny = getminy();
	int maxx = getmaxx();
	int maxy = getmaxy();
	for (int x = maxx; x >= minx; x--) {
		for (int y = miny; y <= maxy; y++) {
			for (int c = 0; c < numSquares; c++) {
				Square * cs = squares[c];
				//if the current co-ordinates actually correspond to a square, then move it
				if (cs->x == x && cs->y == y) {
					bdp->moveSquare(cs,1,0);
				}
			}
		}
	}
	return true;

}

//shifts the block to the left by 1 column
//return true if the shift is successful. Returns false if the shift is not allowed (and nothing is changed)
bool Block::shiftLeft() {
	//check if the move is valid before moving the block
	if (!validMove(-1,0)) return false;

	//shift is valid, so move squares left by 1 column

	//Move the squares that are on the lefthand first
	int minx = getminx();
	int miny = getminy();
	int maxx = getmaxx();
	int maxy = getmaxy();
	for (int x = minx; x <= maxx; x++) {
		for (int y = miny; y <= maxy; y++) {
			for (int c = 0; c < numSquares; c++) {
				Square * cs = squares[c];
				//if the current co-ordinates actually correspond to a square, then move it
				if (cs->x == x && cs->y == y) {
					bdp->moveSquare(cs,-1,0);
				}
			}
		}
	}
	return true;
}


//rotate the block clockwise by 90 degrees
//return true if the rotate is successful. Returns false if the rotate is not allowed (and nothing is changed)
bool Block::rotateRight() {
	int orig_maxy = getmaxy();
	int orig_minx = getminx();

	//store the old co-ordinates of the square in case the rotate is unsuccessful
	pair<int,int> temp[numSquares];
	for (int c = 0; c < numSquares; c++) {
		temp[c].first = squares[c]->x;
		temp[c].second = squares[c]->y;
		// Before attempting rotation undraw all squares
		squares[c]->UnDraw();
	}

	//first switch all the x and y values
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		int temp = cs->x;
		cs->x = cs->y;
		cs->y= temp;
	}

	//then "flip" the block by subtracting x-cord from the max x-cord
	//and add the offset since the original block could of had a positive x cordinate
	int maxx = getmaxx();
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		cs->x = maxx - cs->x + orig_minx;
	}
	cout << "after flip" << endl;
	//if the block has been shifted down after the rotate, we need to translate it back up
	int displacement = orig_maxy - getmaxy();
	//translate the blocks back up if needed
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		cs->y = cs->y + displacement;
	}
	cout << "after displacement" << endl;


	//check to see if the new rotated block can be placed on the board
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		if (!bdp->validPlacement(cs, cs->x, cs->y)) {
			//reset all the squares back to their original positions
			for (int c = 0; c < numSquares; c++) {
				Square * cs = squares[c];
				cs->x = temp[c].first;
				cs->y = temp[c].second;
				// Redraw the Square at it's old position
				cs->Draw();
			}
			return false;

		}
	}

	//otherwise, it is ok to place the block on the board
	cout << "ok to place block on board" << endl;
	//delete the original positions of the block first
	for (int c = 0; c < numSquares; c++) {
		bdp->deleteSquare(temp[c].first, temp[c].second);
	}


	for (int c = 0; c < numSquares; c++) {
		bdp->PlaceSquare(squares[c]);
		cout << "Placed Square at " << squares[c]->x <<"," << squares[c]->y << endl;
	}
	
	return true;
}


//rotate the block counterclockwise by 90 degrees
//return true if the rotate is successful. Returns false if the rotate is not allowed (and nothing is changed)
bool Block::rotateLeft() {
	int orig_maxy = getmaxy();
	int orig_miny = getminy();
	int orig_minx = getminx();
	int minx = getminy();      //new minx is just maxy before switching x and y

	//store the old co-ordinates of the square in case the rotate is unsuccessful
	pair<int,int> temp[numSquares];
	for (int c = 0; c < numSquares; c++) {
		temp[c].first = squares[c]->x;
		temp[c].second = squares[c]->y;
		cout << "original x,y: "<< squares[c]->x <<"," << squares[c]->y << endl;
		// Before attempting rotation undraw all squares
		squares[c]->UnDraw();
	}


	//first switch all the x and y values
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		int temp = cs->x;
		cs->x = cs->y;
		cs->y= temp;
		cout << "after switching x and y,  x,y: "<< squares[c]->x <<"," << squares[c]->y << endl;
	}

	//then "flip" the block by subtracting y-cord from the max y-cord
	//and add the offset since the original block could of had a positive y coordinate
	int maxy = getmaxy();
	//int minx = getminx();
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		cs->y = maxy - cs->y;
		cs->x = cs->x + (orig_minx - minx); 
		cout << "orig_minx is " << orig_minx << "min x now is : " << minx << endl;
		cout << "after flipping and offsetting x,y: "<< squares[c]->x <<"," << squares[c]->y << endl;
	}

	//if the block has been shifted up after the rotate, we need to translate it back down
	int displacement = orig_maxy - getmaxy();
	//translate the blocks back down if needed
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		cs->y = cs->y + displacement;
	}
	cout << "after displacement" << endl;

	//check to see if the new rotated block can be placed on the board
	for (int c = 0; c < numSquares; c++) {
		Square * cs = squares[c];
		if (!bdp->validPlacement(cs, cs->x, cs->y)) {
			cout << "invalid placement of square at " << cs->x << cs->y<< endl;
			//reset all the squares back to their original positions
			for (int c = 0; c < numSquares; c++) {
				Square * cs = squares[c];
				cs->x = temp[c].first;
				cs->y = temp[c].second;
				// Redraw the Square at it's old position
				cs->Draw();
			}
			return false;

		}
	}

	//otherwise, it is ok to place the block on the board
	cout << "ok to place block on board" << endl;
	//delete the original positions of the block first
	for (int c = 0; c < numSquares; c++) {
		bdp->deleteSquare(temp[c].first, temp[c].second);
	}


	for (int c = 0; c < numSquares; c++) {

		bdp->PlaceSquare(squares[c]);
		cout << "Placed Square at " << squares[c]->x <<"," << squares[c]->y << endl;
	}

	return true;
}


//removes a square from the block's list of square
//if the block has 0 squares left, then it is destroyed and it updates the board's score
void Block::remove(Square* s) {

	//there is only 1 square remaining, which means the last square of the block has been removed
	//need to update the score and destroy the block object
	if (numSquares == 1) {
;
		bdp->UpdateScoreBlock(level);

		//!!CHECK THIS!!!

		delete this;
		return;
	}
	//we will remove the pointer to the grid that has been deleted, and move everything after it in the array up by 1 position
		cout << "Deleting Square " << numSquares << " from Block" << endl;
		//look for the square in the array of pointers to squares in the block
		int c = 0;
		while (c < numSquares) {
			//we have found the square
			if (squares[c] == s) {
				//delete the pointer
				delete s;
				squares[c] = NULL;
				break;
			}
			c++;
		}

		//shift all other pointers up by 1 to fill the position of the deleted pointer
		for (int i = c; i < numSquares-1; i++) {
			squares[i] = squares[i+1];
		}
		//set the last pointer to NULL
		squares[numSquares-1]=NULL;
		numSquares--;	
}

bool Block::PlaceOnBoard()
{
	for (int c=0; c < numSquares; c++)
	{
		if(!bdp->PlaceSquare(squares[c])) return false;
	}
	return true;
}

//functions that get the max/min x/y co-ordinates of all the square in the block
int Block::getminx() const{
	int min = width;
	for (int c = 0; c < numSquares; c++) {
		if (squares[c]->x < min) min = squares[c]->x;
	}
	return min;
}
int Block::getminy() const{
	int min = height;
	for (int c = 0; c < numSquares; c++) {
		if (squares[c]->y < min) min = squares[c]->y;
	}
	return min;
}
int Block::getmaxx() const{
	int max = 0;
	for (int c = 0; c < numSquares; c++) {
		if (squares[c]->x > max) max = squares[c]->x;
	}
	return max;
}
int Block::getmaxy() const{
	int max = 0;
	for (int c = 0; c < numSquares; c++) {
		if (squares[c]->y > max) max = squares[c]->y;
	}
	return max;
}

void Block::Draw()
{
	int x;
	int y;
	Xwindow* wnd = bdp->getSideWindow();
	for (int i=0; i<numSquares; i++)
	{
		x = squares[i]->x;
		y = squares[i]->y -2;
		wnd->fillRectangle(x*20,y*20,20,20,Xwindow::Black);
		wnd->fillRectangle(x*20+1,y*20+1,18,18,colour);
	}
}

//Overloaded output function the output a Block depending on the type of block it is
std::ostream& operator<<(std::ostream &out, const Block &b) {
	//get the top left corner and the bottom right corner
	int minx = b.getminx();
	int miny = b.getminy();
	int maxx = b.getmaxx();
	int maxy = b.getmaxy();

	for (int j = miny; j <= maxy; j++) {
		for (int i = minx; i <= maxx; i ++){
			bool print = false;		//temp variable to keep track of whether a square has been printed or not
			//go from the top left until the bottom right and check if each position corresponds to a square
			for (int c = 0; c < b.numSquares; c++) {
				//if the square does have the co-ordinates of (i,j), the print the square there
				if (b.squares[c]->x == i && b.squares[c]->y == j && !print) {
					out << b.squares[c]->getType();
					print = true;
				}
			}
			//if no square has co-ordinates (i,j), then print a blank space
			if (!print) 	out <<" ";
		}
		out << std::endl;
	}

	return out;
}

//default constructor for OBlock
OBlock::OBlock(int level, Board* B): Block(0,2,1,2,0,3,1,3,B,level,'O',Xwindow::Red) {}

IBlock::IBlock(int level, Board* B): Block(0,2,0,3,0,4,0,5,B,level,'I',Xwindow::Green) {}

JBlock::JBlock(int level, Board* B): Block(1,2,1,3,1,4,0,4,B,level,'J',Xwindow::Blue) {}

LBlock::LBlock(int level, Board* B): Block(0,2,0,3,0,4,1,4,B,level,'L',Xwindow::Cyan) {}

TBlock::TBlock(int level, Board* B): Block(0,2,1,2,2,2,1,3,B,level,'T',Xwindow::Yellow) {}

SBlock::SBlock(int level, Board* B): Block(0,2,0,3,1,3,1,4,B,level,'S',Xwindow::Magenta) {}

ZBlock::ZBlock(int level, Board* B): Block(1,2,1,3,0,3,0,4,B,level,'Z',Xwindow::Orange) {}


