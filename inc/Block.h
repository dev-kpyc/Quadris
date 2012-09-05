/*
 * Block.h
 *
 *  Created on: Nov 22, 2011
 *      Author: H3NRY
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>
#include "Window.h"

class Square;
class Board;

//Abstract Block class from which all other classes will be derived from0
class Block {

protected:
	int level; //level that the block was created in
	int numSquares;		//number of squares of the block that remain on the board
	Square* squares[4];	//an array of pointers to squares that comprise the block
	Board* bdp;		//pointer to the board the the block is a part of

	enum orientation {up, right, left, down};	//current orientation of the block. Useful for rotation calculations
	char type;									//different types of blocks, usefuly for printing the blocks
	int colour;

	bool validMove(int i, int j);	//checks to see if a move of i positions horizontally and j positions vertically is valid before moving the block
									//return true if the move is valid, false otherwise

	bool validBlock(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
									//checks if the 4 pairs of co-ordinates for 4 squares are valid configurations
									//return true if the block configuration is valid, false otherwise

	//functions that get the max/min x/y co-ordinates of all the square in the block
	int getminx() const;
	int getminy() const;
	int getmaxx() const;
	int getmaxy() const;

public:
	Block(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Board* bd, int level, char tp, int colour);
				//check for valid grid assignment in superclass constructor
				//throws std::bad_alloc exception is the new block cannot fit onto the grid
	

	~Block();		//destructor

	void draw();
	void undraw();
	bool drop();			//drops the block down 1 row
							//return true if the drop is successful. Returns false if the drop is not allowed (and nothing is changed)
	void dropdown();		//drops the block down to the most bottom row possible
	bool rotateRight();		//rotate the block clockwise by 90 degrees
							//return true if the rotate is successful. Returns false if the rotate is not allowed (and nothing is changed)
	bool rotateLeft();		//rotate the block counterclockwise by 90 degrees
							//return true if the rotate is successful. Returns false if the rotate is not allowed (and nothing is changed)
	bool shiftRight();		//shifts the block to the right by 1 column
							//return true if the shift is successful. Returns false if the shift is not allowed (and nothing is changed)
	bool shiftLeft();		//shifts the block to the left by 1 column
							//return true if the shift is successful. Returns false if the shift is not allowed (and nothing is changed)

	void remove(Square * s);			//removes a square from the block's list of square
							//if the block has 0 squares left, then it is destroyed and it updates the board's score

	char getType() { return type; }			//returns the type of the block (eg.I, J, L, O, S, Z, etc)
	int getColour() { return colour; }
	
	void Draw(); // Draws the Block in the side window
	bool PlaceOnBoard();

	friend std::ostream& operator<<(std::ostream &out, const Block &b);	//Overloaded output function the output a Block depending on the type of block it is


	//bool PlaceBlock();

};

//O Block Subclass
class OBlock : public Block{
public:
	OBlock(int lvl, Board* B);
};
//I Block Subclass
class IBlock : public Block{
public:
	IBlock(int lvl, Board* B);
};
//L Block Subclass
class LBlock : public Block{
public:
	LBlock(int lvl, Board* B); 
};
//J Block Subclass
class JBlock : public Block{
public:
	JBlock(int lvl, Board* B);
};
//S Block Subclass
class SBlock : public Block{
public:
	SBlock(int lvl, Board* B);
};
//Z Block Subclass
class ZBlock : public Block{
public:
	ZBlock(int lvl, Board* B);
};
//T Block Subclass
class TBlock : public Block{
public:
	TBlock(int lvl, Board* B);
};

#endif /* BLOCK_H_ */
