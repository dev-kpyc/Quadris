/*
 * Interpreter.h
 *
 *  Created on: Nov 22, 2011
 *      Author: H3NRY
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_
class TrieNode;
class Board;
#include <string>
#include <iostream>

class Interpreter {
	TrieNode * commands;	//list of available command names stored as a Trie. Can be used for autocompeletion
	Board * bdp;			//pointer to the board

public:
	Interpreter();						//default constructor
	Interpreter(Board*);
	~Interpreter();						//destructor
	std::istream & read(std::istream & in);		//reads in commands from the input stream and calls the appropriate commands for the board (if the input if valid)
										//returns the input stream after reading
	void rename(std::string newname, std::string oldname); //renames a command with the oldname to a command with the newname

};
#endif /* INTERPRETER_H_ */
