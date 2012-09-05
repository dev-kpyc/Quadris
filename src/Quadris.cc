//============================================================================
// Name        : Quadris.cpp
// Author      : Kevin Pyc, Henry Shi
// Version     :
// Copyright   : 
// Description : 
//============================================================================

#include <iostream>
#include <stdlib.h>
#include "Interpreter.h"
#include "Board.h"
#include "Window.h"
using namespace std;
int Level::Seed = getpid();

int main(int argc, char *argv[]) 
{	
	bool textmode=false;
	Xwindow* MainWindow = 0;
	Xwindow* SideWindow = 0;

	for (int c=1; c<argc; c++)
	{
		if (string(argv[c]) == "-text") 
		{
			textmode = true;
			cout << "TextMode = Active" << endl;
		}
		else if (string(argv[c]) == "-seed")
		{
			c++;
			Level::Seed = atoi(argv[c]);
			cout << "Seed = "<<Level::Seed<<endl;
		}
	}	
	if (!textmode) 
	{
		SideWindow = new Xwindow(80,80);
		MainWindow = new Xwindow(200,400);
	}
		
	Board* B = new Board(MainWindow, SideWindow);
	Interpreter I(B);
	cout << *B << endl;
	while (I.read(cin)) { cout << *B; }
	
	delete B;
	delete SideWindow;
	delete MainWindow;
	return 0;
}
