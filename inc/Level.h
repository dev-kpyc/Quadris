/*
 * level.h
 *
 *  Created on: 2011-11-22
 *      Author: KPYC
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <fstream>
#include "PRNG.h"
#include "Block.h"


class Level
{
	protected:
		int num;
		PRNG RND;
		Board * bdp;
		Level(Board * board, int num);
	public:
		static int Seed;
		int getLevelNumber() { return num; }
		virtual Block* NextBlock() = 0;
};
// Derived Classes Represent Specific Levels

class Level0 : public Level
{
	std::ifstream& sequence;
	public:
		Level0(Board * board);
		Block* NextBlock();
};

class Level1 : public Level
{
public:
	Level1(Board * board);
	Block* NextBlock();
};
class Level2 : public Level
{
public:
	Level2(Board * board);
	Block* NextBlock();
};
class Level3 : public Level
{
public:
	Level3(Board * board);
	Block* NextBlock();
};

#endif /* LEVEL_H_ */
