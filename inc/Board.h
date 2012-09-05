/*
 * board.h
 *
 *  Created on: 2011-11-22
 *      Author: KPYC
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include "Block.h"
#include "Square.h"
#include "Level.h"
#include "Window.h"

const int height = 18;
const int width = 10;

class Board
{
   Level* LV; //Stores the board's active level
   
   Xwindow* Main; //Stores the main window for drawing the pieces
   Xwindow* Side; //Side window for drawing the next block
   
   bool isInit;		//	Flags for determining the game state
   bool isGameOver; //
   
   int Score;	//	For Storing the Game's Score
   int HiScore; //
   
   Square* (Grid[height][width]); // Grid of Square Pointers					
   
   Block* NextBlock;	// Next Block and Active Block in
   Block* ActiveBlock;  // Use by Board
   
   bool isActive(){ return isInit && !isGameOver; } // Game is Actively Running
   bool isGraphical() { return Main != NULL && Side != NULL; } // Determines whether we should draw Xwindow components
   
   bool FullRow(int r); // True if Row r is full
   void ClearRow(int r); // Clears Row r
   void ClearAll(); // Clears all rows that are full
   void GameOver(); // Sets the game state to game over

   public:
   Board(Xwindow* Main, Xwindow* Side);
   ~Board();
   Xwindow* getMainWindow() { return Main; }
   Xwindow* getSideWindow() { return Side; }
   void Initialize();
   // true if board at row i column j contains a block
   bool isFull(int i, int j) const { return Grid[i][j] != NULL; }
   // true if board at row i column j is empty
   bool isEmpty(int i, int j) const { return Grid[i][j] == NULL; }
   
   bool validMove(Square* S, int x, int y);
   bool moveSquare(Square* S, int x, int y);
   bool PlaceSquare(Square* S);
   
   // Commands which control the active block
   void ShiftLeft();
   void ShiftRight();
   void DropDown();
   void Drop();
   void Clockwise();
   void Counterclockwise();
   // Commands which control the board state
   void ChangeLevel(int modifier);
   void Restart();
   
   // Attempts to put next block on the board, if there is a collision return false, otherwise
   // place the block and return true
   bool PlaceBlock();
   // change LV to newLevel
   // call LV's nextBlock function
   void GetNextBlock();
   // Run Board Logic after a block has been dropped down
   void Update();
   // update score after block from level n is removed
   void UpdateScoreBlock(int n);
   void UpdateScoreLine(int n);
   
   
   //Henry's additions:
   //checks if it is valid to place a square with the given x,y co-ordinates
   //assumes that square can override another square if they are from the same block
   bool validPlacement(Square* S, int x, int y);
   //deletes a Square pointer located at co-ordinates x,y from the Board
   bool deleteSquare(int x, int y);

   friend std::ostream& ::operator<<(std::ostream &out, const Board &B);
};

#endif /* BOARD_H_ */
