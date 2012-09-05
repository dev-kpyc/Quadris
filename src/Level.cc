/*
 * level.cc
 *
 *  Created on: 2011-11-22
 *      Author: KPYC
 */
#include <iostream>
#include <stdlib.h>
#include "Level.h"

Level::Level(Board * board, int num) : bdp(board), num(num), RND(PRNG(Seed)) {}

Level0::Level0(Board * board): Level(board, 0), sequence(*new std::ifstream("sequence.txt")) {}

Block* Level0::NextBlock()
{
	if (!sequence.is_open())
	{
		std::cerr << "File sequence.txt does not exist" << std::endl;
		std::cerr << "Exiting with error code 47" << std::endl;
		exit(47);
	}

	char b;	
	Block* NextBlock;
	
	sequence>>b;
	// If EOF is reached reopen the file and start again
	if (sequence.eof()) 
	{
		sequence.clear();
		sequence.seekg(0);
		sequence>>b;
	}	
		switch (b){
		case 'I':
			NextBlock = new IBlock(num,bdp);
			break;
		case 'J':
			NextBlock = new JBlock(num,bdp);
			break;
		case 'L':
			NextBlock = new LBlock(num,bdp);
			break;
		case 'O':
			NextBlock = new OBlock(num,bdp);
			break;
		case 'S':
			NextBlock = new SBlock(num,bdp);
			break;
		case 'Z':
			NextBlock = new ZBlock(num,bdp);
			break;
		case 'T':
			NextBlock = new TBlock(num,bdp);
			break;
		default:
			std::cerr << "Unrecognized Block "<<b<<" in sequence.txt"<<std::endl;
		}

		if (NextBlock == NULL) std::cerr << "Next Block could not be allocated" << std::endl;

		return NextBlock;
	
}

Level1::Level1(Board * board) : Level(board, 1) {}

Block* Level1::NextBlock()
{
	int random = RND(1, 12);
	Block* NextBlock;

	switch (random)
	{
		case 1:
			NextBlock = new SBlock(num,bdp);
			break;
		case 2:
			NextBlock = new ZBlock(num,bdp);
			break;
		case 3: case 4:
			NextBlock = new IBlock(num,bdp);
			break;
		case 5: case 6:
			NextBlock = new JBlock(num,bdp);
			break;
		case 7: case 8:
			NextBlock = new LBlock(num,bdp);
			break;
		case 9: case 10:
			NextBlock = new OBlock(num,bdp);
			break;
		case 11: case 12:
			NextBlock = new TBlock(num,bdp);
			break;
	}

}

Level2::Level2(Board * board) : Level(board, 2) {}

Block* Level2::NextBlock()
{
	int random = RND(1, 7);
	Block* NextBlock;
	
		switch (random)
	{
		case 1:
			NextBlock = new SBlock(num,bdp);
			break;
		case 2:
			NextBlock = new ZBlock(num,bdp);
			break;
		case 3: 
			NextBlock = new IBlock(num,bdp);
			break;
		case 4:
			NextBlock = new JBlock(num,bdp);
			break;
		case 5:
			NextBlock = new LBlock(num,bdp);
			break;
		case 6:
			NextBlock = new OBlock(num,bdp);
			break;
		case 7:
			NextBlock = new TBlock(num,bdp);
			break;
	}
}

Level3::Level3(Board * board) : Level(board, 3) {}

Block* Level3::NextBlock()
{
	int random = RND(1, 9);
	Block* NextBlock;
	
		switch (random)
	{
		case 1: case 2:
			NextBlock = new SBlock(num,bdp);
			break;
		case 3: case 4:
			NextBlock = new ZBlock(num,bdp);
			break;
		case 5: 
			NextBlock = new IBlock(num,bdp);
			break;
		case 6:
			NextBlock = new JBlock(num,bdp);
			break;
		case 7:
			NextBlock = new LBlock(num,bdp);
			break;
		case 8:
			NextBlock = new OBlock(num,bdp);
			break;
		case 9:
			NextBlock = new TBlock(num,bdp);
			break;
	}
}
