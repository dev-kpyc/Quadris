/*
 * Square.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: pascal
 */

#include "Square.h"
#include "Block.h"

//default constructor
//initialize all members to 0
Square::Square(): x(x), y(y), bkp(NULL) {}

//constructor with arguments to the x and y positions of the square as well as the block and board that the square is a part of and its type
Square::Square(int x, int y, Block * bk, Xwindow* xw,char type): x(x), y(y), bkp(bk), Xw(xw), type(type) {}

void Square::Remove() {
	UnDraw();
	bkp->remove(this);
}
//destructor will call block's remove method, with the square's pointer as argument, and remove the square from the block's list of squares
Square::~Square() {
	UnDraw();
}

void Square::Draw() {
	if (Xw != NULL){
		Xw->fillRectangle(x*20,y*20+40,20,20,Xwindow::Black);
		Xw->fillRectangle(x*20+1,y*20+41,18,18,bkp->getColour());
	}
}
void Square::UnDraw(){
	if (Xw != NULL){
		Xw->fillRectangle(x*20,y*20+40,20,20,Xwindow::White);
	}
}

std::ostream& operator<<(std::ostream &out, const Square &S) {
	out << S.type;
	return out;
}
