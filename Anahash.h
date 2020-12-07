// CMSC 341, Spring 2019
// Project 5: Finding anagrams by hashing

#ifndef _ANAHASH_H
#define _ANAHASH_H

#include<set>
#include<string>
#include<algorithm>
#include<exception>

using namespace std;

class Grader;

class Anahash {
public:

	friend Grader;

	// Maximum hash table size (2^16)
	const unsigned int HT_SIZE_LIMIT = (1 << 16);

	// Create a Anahash object with hash table of size 'htSize'.  If
	// 'htSize' is greater than HT_SIZE_LIMIT or less than 1, throw a
	// range_error exception.
	Anahash(int htSize);

	// Copy constructor
	Anahash(const Anahash& rhs);

	// Assignment operator
	Anahash& operator=(const Anahash& rhs);

	// Destructor
	~Anahash();

	// Insert 'line' into hash table.  Return true if a new entry is
	// created, false if the line is already in the table.
	bool insert(string line);

	// Search for 'line' in the hash table.  Return true if found, false
	// otherwise.
	bool search(string line);

	// If 'line' is in the the hash table, return its set of anagrams,
	// including 'line'.  If 'line' is not in the hash table, return an
	// emtpy set of strings.
	set<string> getAnagrams(string line);

	// Dump all non-empty lists from the hash table.  Print the hash
	// value in hexadecimal and the strings in the list.
	void dump();

private:
	set<string> *m_ht;     // Array of string sets
	int m_htSize;          // Size of hash table

	// Hash function.  Should hash anagrams to the same value (good
	// collision) while minimizing the number of non-anagrams that hash
	// to the same value (bad collisions).
	static unsigned int anaHash(string line);

	//********************************************************
	//
	// Other private helper functions should be declared here.
	//
	//********************************************************

};

#endif
