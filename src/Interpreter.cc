#include "Interpreter.h"
#include "Trie.h"
#include "Square.h"
#include "Block.h"
#include "Board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//default constructor
Interpreter::Interpreter() {
	commands = new TrieNode();
	//read in the list of commands
	ifstream ifs("commands.txt");
	string command;
	//insert the commands into the Trie
	while (ifs >> command) {
		commands->insert(command, command);
	}
}

//default constructor with pointer to board as parameter
Interpreter::Interpreter(Board * board) {
	commands = new TrieNode();
	//read in the list of commands
	ifstream ifs("commands.txt");
	string command;
	//insert the commands into the Trie
	while (ifs >> command) {
		commands->insert(command, command);
	}
	bdp = board;
}

//reads in commands from the input stream and calls the appropriate commands for the board (if the input if valid)
//returns the input stream after reading
istream& Interpreter::read(istream & in) {
	string line;
	string command;
	string partial_command;
	string word;
	string filename;
	int prefix = 1;

	//get a line from the inputstream
	getline(in, line);
	if (in.fail()) return in;   //if the read has failed, the return the istream

	istringstream iss(line);

	//check to see if there is a numerical prefix
	if ('0'<= iss.peek() && iss.peek() <='9') {
		cout << "peeking" << iss.peek() << endl;
		iss >> prefix;
		iss >> partial_command;
	}
	else {
		iss >> partial_command;	//read the first command
	}

	//lookup the prefix to see if it matches a command
	command = commands->Lookup(partial_command);

	//if the command is to rename something
	if (command == "rename") {
		string oldname;
		string newname;
		string commandname;
		iss >> oldname;
		iss >> newname;
		//lookup the oldname in case it has been renamed
		commandname = commands->Lookup(oldname);
		if (command == "") {
			cout << "Ambiguous original command name" << endl;
		}

		//if the new assigned name is ambiguous, cannot rename it
		//CHECK THIS
		/*
		if (commands->Lookup(newname) == "") {
			cout << "Ambiguous new command name" << endl;
			return in;
		}
		*/


		commands->remove(oldname);
		commands->insert(newname, commandname);
		return in;
	}

	//if the prefix is ambiguous, do nothing
	if (command == "") {
		cout << "Cannot Process Command" << endl;
		return in;
	}

	//loop in the case of a prefix
	while (prefix > 0) {
		//adding a word
		if (command == "start") {
			bdp->Initialize();
		}
		else if (command == "left") {
		  bdp->ShiftLeft();
		  cout << "moving left" << endl;
		}
		//removing a word
		else if (command == "right") {
			bdp->ShiftRight();
		}
		//prints a list of possible autocompletions for word, in alphabetical order
		else if (command == "down") {
			bdp->Drop();
		}
		//read commands from file
		else if (command == "drop") {
			bdp->DropDown();
		}
		else if (command == "clockwise") {
			bdp->Clockwise();
		}
		//FIX THIS!!!!
		else if (command == "counterclockwise") {
			bdp->Counterclockwise();
		}
		else if (command == "levelup") {
		  bdp->ChangeLevel(1);
		}
		else if (command == "leveldown") {
		  bdp->ChangeLevel(-1);
		}
		else if (command == "restart") {
		  bdp->Restart();
		  return in;
		}
		prefix--;
	}
	return in;

}
//default destructor
Interpreter::~Interpreter() {
	delete commands;
}
