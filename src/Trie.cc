#include "Trie.h"
#include <string>
#include <iostream>

using namespace std;

//defualt constructor
TrieNode::TrieNode(): command("") {
	for (int c = 0; c < numChars; c++) {
		letters[c] = NULL;
	}
}
//adds a new command with command_name to the Trie
void TrieNode::insert(string command, string command_name) {
   //convert the string into a c-style char array for easier processing into the trie
   const char * wrd = command.c_str();
   TrieNode *cur = this;
   //loop over the elements of the char array
   while (*wrd != '\0') {
      int index = *wrd-'a';
      //if the first character in wrd is not a child of the trie, we need to add the character as a child of the trie
      if (cur->letters[*wrd-'a'] == NULL) {
         cur->letters[*wrd-'a'] = new TrieNode();
      }
      //iterate to the next child of the tree that corresponds to the next character of word
      cur = cur->letters[*wrd-'a'];
      wrd++;
   }
   //at the end of inserting the character array into the trie, the last node should have the isWord field marked as true
   cur->command = command_name;
   cout << "inserted command: " << command << endl;
}

//removes a command from the Trie
void TrieNode::remove(string command) {
   //convert the string into a c-style char array for easier processing into the trie
   const char * wrd = command.c_str();
   TrieNode *cur = this;
   //loop over the elements of the char array
   while (*wrd != '\0') {
      //if the first character in wrd is not a child of the trie, then we cannot possibly remove a word that is not in the trie. break
      if (cur->letters[*wrd-'a'] == NULL) {
         return;
      }
      //iterate to the next child of the tree that corresponds to the next character of word
      cur = cur->letters[*wrd-'a'];
      wrd++;
   }
   //at the end of iterating the character array in the trie, the last node should have the isWord field marked as false
   cur->command = "";
}

//looks up to see if a prefix matches exactly one command in the Trie.
//returns an empty string if the prefix does not match a command or if the prefix matches more than one command
string TrieNode::Lookup(string prefix) {

   //convert the string into a c-style char array for easier processing into the trie
   const char * wrd = prefix.c_str();
   TrieNode * cur = this;
   //loop over the elements of the char array
   while (*wrd != '\0') {
      //if the first character in wrd is not a child of the trie, then the word is not in the trie. NULL is returned
      if (cur->letters[*wrd-'a'] == NULL) {
    	 cout << "reached after the prefix" << endl;
         return "";
      }
      //iterate to the next child of the tree that corresponds to the next character of word
      cur = cur->letters[*wrd-'a'];
      wrd++;
   }
	//check how many occurances of commands after prefix are there
	int count = cur->countallwords();
	cout << "found " << count << " occurances of the prefix" << endl;
	//if the prefix does not match a command or if the prefix matches more than one command, then return null string
	if (count != 1) return "";

	//iterate over the rest of the Trie to find the command
   //should be ok b/c there should only be 1 command even if we concatenate all the commands
   return cur->getallcommands();
}


//count all possible commands from a given TrieNode to an ostream
int TrieNode::countallwords() {
   int count = 0;
	//if the node is NULL, it is not part of a word and the original ostream is returned
   if (this->command != ""){
      count++;
   }

   //print all possible words in the children of the TrieNode
   for (char c = 'a'; c <= 'z'; c++) {
      //recursively go through each letter
	  if (this->letters[c-'a'] != NULL){
		//recursively go through each letter and add to the prefix according to each letter from a-z
		count += this->letters[c-'a']->countallwords();
	   }
   }
   return count;
}

//returns the concatenation of all the strings in the Trie
string TrieNode::getallcommands() {
	string rtn = this->command;

	//recursively go through each TrieNode
	for (char c = 'a'; c <= 'z'; c++) {
		if (this->letters[c-'a'] != NULL){
			rtn += this->letters[c-'a']->getallcommands();
		}
	}
	return rtn;
}

//destructor
TrieNode::~TrieNode() {
	for (char c = 'a'; c <= 'z'; c++) {
	   if (letters[c-'a'] != NULL) delete letters[c-'a'];
   }
}

