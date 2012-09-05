// Board.cc
// Created by Kevin Pyc and Henry Shi
// Dec 2011

#include "Board.h"
#include "Block.h"
#include "Square.h"
#include <sstream>

#ifdef VERBOSE
	#define VOUT(exp) std::cout exp
#else
	#define VOUT(exp)
#endif

Board::Board(Xwindow* Main, Xwindow* Side) : Score(0), HiScore(0), isInit(false), isGameOver(false), Main(Main), Side(Side)
{
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			Grid[i][j] = NULL;
		}
	}
	if (isGraphical()) 
	{
		Main->drawString(5,10,"Level:");
		Main->drawString(180,10,"1");
		Main->drawString(5,20,"Score:");
		Main->drawString(180,20,"0");
		Main->drawString(5,30, "Hi Score:");
		Main->drawString(180,30,"0");
		Main->fillRectangle(0,35,200,2,Xwindow::Black);
	}
}
Board::~Board()
{
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			if (isFull(i,j)) 
			{
				Grid[i][j]->Remove();
			}
		}
	}
	delete LV;
	delete NextBlock;
}

void Board::Initialize()
{
	VOUT(<< "Initialize" << std::endl);
	LV = new Level1(this);
	ActiveBlock = LV->NextBlock();
	ActiveBlock->PlaceOnBoard();
	VOUT(<< "Created Block " << ActiveBlock->getType() << std::endl);
	NextBlock = LV->NextBlock();
	VOUT(<< "Created Block " << NextBlock->getType() << std::endl);
	if (isGraphical()) NextBlock->Draw();
	isInit=true;
}

void Board::Restart()
{
   for (int i=0; i<height; i++)
      for (int j=0; j<width; j++)
      {
      	
         if (isFull(i,j)) 
         {
         	VOUT(<< i << " " << j << " is full" <<std::endl);
         	delete Grid[i][j];
         	VOUT(<<"Setting "<<i<<" "<<j<< " NULL"<<std::endl);
      	 	Grid[i][j] = NULL;
         }
        
      }  
   Score = 0;
   isGameOver = false;
   if (isGraphical()) Main->fillRectangle(0,60,200,340,Xwindow::White);
   delete LV;
   delete NextBlock;
   Initialize();
}

void Board::Update()
{
   ClearAll(); // Clear all rows that are completely filled and update the grid
   if (PlaceBlock()) 
   { 	
   		ActiveBlock = NextBlock;
   		NextBlock = LV->NextBlock();
   		if (isGraphical())
   		{
   			Side->fillRectangle(0,0,100,100,Xwindow::White);
   			NextBlock->Draw();
		}
   } else { GameOver(); }
}
void Board::GameOver() 
{ 
	isGameOver = true; 
	if (isGraphical())
	{
		Main->fillRectangle(0,60,200,340,Xwindow::White);
		Side->fillRectangle(0,0,80,80,Xwindow::White);
		Main->drawString(70,150,"GAME OVER");
	}
}

// Returns true if the row is completely filled by squares, otherwise returns false
bool Board::FullRow(int r)
{
   for (int i=0; i<width; i++)
      if (isEmpty(r,i)) return false;
   VOUT(<<"Row "<<r<<" is full"<<std::endl);
   return true;
}
void Board::ClearRow(int r)
{
	VOUT(<<"Clearing row "<<r<<std::endl);
	// Delete all squares in the row
	for (int k=0; k<width; k++) 
	{ 
		Grid[r][k]->Remove(); 
		Grid[r][k] = NULL;
	}
	VOUT(<<"Moving Rows Down"<<std::endl);
	// Next move all squares in all rows above r down by one
    for (int i=r; i>0; i--)
    	for (int j=0; j<width; j++)
    		if (isFull(i-1,j)) moveSquare(Grid[i-1][j],0,1);
}
// Runs ClearRow for each full row in the grid
void Board::ClearAll()
{
   int numRows = 0;

   for (int r=0; r<height; r++)
   {
      if (FullRow(r))
      {
         numRows++;
         ClearRow(r);
      }
   }
   UpdateScoreLine(numRows);
}

void Board::UpdateScoreBlock(int n)
{
	Score = Score + (n + 1)*(n + 1);
	if (Score > HiScore) HiScore = Score;
	if (isGraphical())
	{
		std::stringstream ss;
		ss << Score;
		Main->fillRectangle(180,11,20,7,Xwindow::White);
		//std::cout << ss.str() << std::endl;
		Main->drawString(180,20,ss.str());
		ss.str("");
		ss << HiScore;
		//std::cout << ss.str() << std::endl;
		Main->fillRectangle(180,21,20,7,Xwindow::White);
		Main->drawString(180,30,ss.str());
	}
}
void Board::UpdateScoreLine(int n)
{
   // Increase the score if any lines were cleared
   if (n > 0)
   {
   		Score += (n + LV->getLevelNumber()) * (n + LV->getLevelNumber());	
   
   if (Score > HiScore) HiScore = Score;
   	if (isGraphical())
	{
		std::stringstream ss;
		ss << Score;
		Main->fillRectangle(180,11,20,7,Xwindow::White);
		std::cout << ss.str() << std::endl;
		Main->drawString(180,20,ss.str());
		ss.str("");
		ss << HiScore;
		std::cout << ss.str() << std::endl;
		Main->fillRectangle(180,21,20,7,Xwindow::White);
		Main->drawString(180,30,ss.str());
	}
	}
}

bool Board::validMove(Square* S, int x, int y)
{
	int x1 = S->x;
	int y1 = S->y;
	if (((y1+y) >= 0) && ((y1+y) < height)	&& ((x1+x) >= 0) && ((x1+x) < width)) {
		if (isEmpty(y1+y,x1+x)) return true;
		//check to make sure that the occupied square is not a square from the same block
		else {
			if (Grid[y1+y][x1+x]->getBlock() == S->getBlock()) return true;
		}
	}
	else return false;
}

bool Board::moveSquare(Square* S, int x, int y)
{
	int x1 = S->x;
	int y1 = S->y;
	Grid[y1+y][x1+x] = S;
	S->UnDraw();
	S->x += x;
	S->y += y;
	S->Draw();
	Grid[y1][x1] = NULL;
	return true;
}

void Board::ShiftRight() 
{ 
	if(isActive()) ActiveBlock->shiftRight(); 
}
void Board::ShiftLeft() 
{ 
	if(isActive()) ActiveBlock->shiftLeft(); 
}
void Board::DropDown()
{
	if(isActive()) ActiveBlock->dropdown();
}
void Board::Drop()
{
	if(isActive()) ActiveBlock->drop();
}
void Board::Clockwise()
{
	if(isActive()) ActiveBlock->rotateRight();
}
void Board::Counterclockwise()
{
	if(isActive()) ActiveBlock->rotateLeft();
}
void Board::ChangeLevel(int modifier)
{
	int newLV = LV->getLevelNumber() + modifier;
	// Delete the old level
	if (newLV < 0 || newLV > 3) 
	{
		std::cerr << "Level Out of Range" << std::endl;
		return;
	}
	
	delete LV;
	
	switch (newLV)
	{
		case 0:
			LV = new Level0(this);
			break;
		case 1:
			LV = new Level1(this);
			break;
		case 2:
			LV = new Level2(this);
			break;
		case 3:
			LV = new Level3(this);
			break;
	}
	if (isGraphical())
	{
		std::stringstream ss;
		ss << LV->getLevelNumber();
		Main->fillRectangle(180,0,20,10,Xwindow::White);
		Main->drawString(180,10,ss.str());	
	}
}

bool Board::PlaceSquare(Square* S)
{
	if (isFull(S->y,S->x)) return false;
	else Grid[S->y][S->x] = S;
	S->Draw();
	return true;
}

bool Board::PlaceBlock()
{
	return NextBlock->PlaceOnBoard();
}

std::ostream& operator<<(std::ostream &out, const Board &B)
{

if (!B.isInit)
{
out
<<"                                888         d8b         "<<std::endl
<<"                                888         Y8P         "<<std::endl
<<"                                888                     "<<std::endl
<<" .d88888 888  888  8888b.   .d88888 888d888 888 .d8888b "<<std::endl
<<"d88  888 888  888     88b  d88  888 888P    888 88K     "<<std::endl
<<"888  888 888  888 .d888888 888  888 888     888  Y8888b."<<std::endl
<<"Y88b 888 Y88b 888 888  888 Y88b 888 888     888      X88"<<std::endl
<<"  Y88888   Y88888  Y888888   Y88888 888     888  88888P'"<<std::endl
<<"     888                                                "<<std::endl
<<"     888                                                "<<std::endl
<<"     888                                                "<<std::endl
<<std::endl<<"Type 'start' to begin"<<std::endl;
}
else if (B.isGameOver)
{
out
<<" __              ___     __        ___  __  "<<std::endl
<<"/ _`  /\\   |\\/| |__     /  \\ \\  / |__  |__) "<<std::endl
<<"\\__> /~~\\  |  | |___    \\__/  \\/  |___ |  \\ "<<std::endl
<<std::endl<<"Type 'restart' to try again"<<std::endl<<std::endl;
}
else
{

	// Print Level Score and Hi Score information
   out << "Level:       " << B.LV->getLevelNumber() << std::endl;
   out << "Score:       " << B.Score << std::endl;
   out << "Hi Score:    " << B.HiScore << std::endl;
   out << "----------" << std::endl;

   // Print the Square Grid
   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         if (B.isFull(i,j)) out << *(B.Grid[i][j]);
         else out << " ";
      }

      out << std::endl;
   }

   // Print the Next Block
   out << "----------" << std::endl;
   out << "Next:" << std::endl;
   out << *(B.NextBlock);
}
   return out;

}


//Henry's Additions:

//checks if it is valid to place a square with the given x,y co-ordinates
//assumes that square can override another square if they are from the same block
bool Board::validPlacement(Square* S, int x, int y)
{
	if (((y) >= 0) && ((y) < height) && ((x) >= 0) && ((x) < width)) {
		if (isEmpty(y,x)) return true;
		//check to make sure that the occupied square is not a square from the same block
		else {
			if (Grid[y][x]->getBlock() == S->getBlock()) {
				std::cout << "collison but squares from same block, so all good" << std::endl;
				return true;
			}
		}
	}
	else return false;
}

//deletes a Square pointer from the Board
bool Board::deleteSquare(int x, int y) {
	std::cout << "deleting square at: "<< x << y << std::endl;
	Grid[y][x] = NULL;
	return true;
}

