/*
 * Trie.h
 *
 *  Created on: Nov 22, 2011
 *      Author: pascal
 */

#ifndef TRIE_H_
#define TRIE_H_
#include <string>

const int numChars = 27;

class TrieNode {
    std::string command;					//command that the string ending at this TrieNode corresponds to
    TrieNode *letters[numChars];			//array of pointers to TrieNodes, one for each letter of the alphabet
	int countallwords();					//count all possible commands from a given TrieNode to an ostream
	std::string getallcommands();			//returns the concatenation of all the strings in the Trie

public:
    TrieNode();						//default constructor
    ~TrieNode();					//destructor
	void insert(std::string command, std::string command_name);	//adds a new command with command_name to the Trie
	void remove(std::string command);	//removes a command from the Trie
	std::string Lookup(std::string prefix);	//looks up to see if a prefix matches exactly one command in the Trie.
									//returns an empty string if the prefix does not match a command or if the prefix matches more than one command

};
#endif /* TRIE_H_ */
