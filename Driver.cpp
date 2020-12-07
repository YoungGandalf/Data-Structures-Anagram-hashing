//Adam Hereth

// CMSC 341, Spring 2019
// Project 5: Finding anagrams by hashing
// Sample driver program

#include "Anahash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  Anahash aH( 1 << 16 );  // Table of size 2^16

  // Read the sample data an insert into the hash table.

  string fileName = "anagrams_single.txt";
  ifstream inFp( fileName );

  if ( inFp.is_open() ) {
    string line;
    while ( getline( inFp, line ) ) {
      if ( line.size() > 0 ) {
	aH.insert( line );
      }
    }
    inFp.close();
  } else {
    cerr << "File " << fileName << " could not be opened\n";
  }

  // Use getAnagrams to retrieve the anagrams of "wired".

  
  cout << "wired:\n";
  auto ana = aH.getAnagrams("wired");
  for (auto itr = ana.begin(); itr != ana.end(); itr++)
    cout << "   " << *itr << endl;
  cout << endl;

  
  
  // Dump the contents of the hash table.

  cout << "Full dump of table:\n";
  aH.dump();
  
  return 0;
}
  
  
