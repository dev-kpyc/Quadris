#ifndef _SQUARE_H
#define _SQUARE_H
#include <iostream>

#include "Window.h"

class Board;
class Block;

class Square {
	Block* bkp;
	Xwindow* Xw;
	//3 boolean variables to indicate if the square is the bottom-most, left-most and/or rightmost of a block
	bool isbottom;
	bool isright;
	bool isleft;
	char type;			//different types of blocks, usefuly for printing the blocks

public:
	int x, y;
	Square(); //default constructor
	//constructor with arguments to the x and y positions of the square as well as the board that the square is a part of and its type
	Square(int x, int y, Block * bk, Xwindow* Xw, char type); 
	~Square();				
	void Draw();
	void UnDraw();
	void Remove();
	char getType() { return type; }			//returns the type of the block (eg.I, J, L, O, S, Z, etc)
	Block * getBlock () {return bkp;}		//returns the pointer to the block that the square belongs to

	friend std::ostream& operator<<(std::ostream &out, const Square &S);	//Overloaded output function the output a square depending on the type of block that it belongs to
};

#endif
