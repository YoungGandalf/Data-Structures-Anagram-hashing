//Adam Hereth

#include "Anahash.h"
#include <iostream>

/*
This is the constructor for the Anahash class. It must be provided with htSize, the size of the hash table. If htSize is greater than HT_SIZE_LIMIT or less than 1, throw a range_error exception; otherwise, allocate the hash table (m_ht) and save the table size (m_htSize).
*/
Anahash::Anahash(int htSize)
{
  if (htSize > HT_SIZE_LIMIT or htSize < 1)
    {
      throw range_error("Size is out of range");
    }
  else
    {
      m_ht = new set<string> [htSize];
      m_htSize = htSize;
    }
  for (int i = 0; i < m_htSize; i++)
    {
      set<string> hashtable;
      m_ht[i] = hashtable; 
    }
  cout << "N = " << m_htSize << endl; ;
}

Anahash::Anahash(const Anahash & rhs)
{ 
    cout << "copy constructor " << endl;
    m_htSize = rhs.m_htSize;
    m_ht = new set<string>[m_htSize];
    for (int i = 0; i < m_htSize; i++)
      {
	m_ht[i] = rhs.m_ht[i];
      }
}

Anahash & Anahash::operator=(const Anahash & rhs)
{
  cout << "operator= called " << endl;
  delete [] m_ht;
  m_htSize = rhs.m_htSize;
  m_ht = new set<string>[m_htSize];
  for (int i = 0; i < m_htSize; i++) {
    m_ht[i] = rhs.m_ht[i];
  }

  return *this;
}

// Destructor for the Anahash class. All dynamically-allocated data
// must be deallocated.
Anahash::~Anahash()
{
  delete [] m_ht;
}

// Insert 'line' into hash table.  Return true if a new entry is
// created, false if the line is already in the table.
bool Anahash::insert(string line)
{
  int ascValue;
  //sets x to the hashed value of the string
  int x = anaHash(line);
  x = x % m_htSize;
  bool a = true;
  //if the string is in the hash, return true
  if(search(line) == true)
    {
      return true;
    }
  else
    {
      //if the anagrams being compared are anagrams insert it. 
      if(isAnagram(line, *m_ht[x].begin()) == true) 
	{
	  m_ht[x].insert(line); 
	}
      //same as above but different cases; if the index is empty and if its not and the
      //word is in the hash but not an anagram
      else if(isAnagram(line, *m_ht[x].begin()) == false)
	{
	  for(unsigned int i = ascValue; i < m_htSize; i++)
	    {
	      if(m_ht[i].empty())
		{
		  m_ht[x].insert(line);
		  a = false;
		}
	      else if(!m_ht[i].empty() and isAnagram(*m_ht[i].begin(), line))
		{
		  m_ht[x].insert(line);
		  a = false;
		}
	    }
	  if(a == true)
	    {
	      //same as above but goes through 0 to the asc value instead of looping through
	      //the ascii value to the size
	      for(unsigned int i = 0; i < ascValue; i++)
		{
		  if(m_ht[i].empty())
		    m_ht[x].insert(line);
		  else if(!m_ht[i].empty() and isAnagram(*m_ht[i].begin(), line))
		    m_ht[x].insert(line);
		}
	    }
	}
    }
  return false;
}

// Search for 'line' in the hash table.  Return true if found, false
// otherwise.
bool Anahash::search(string line)
{
  unsigned int ascValue = anaHash(line);
  //loops through hash similar to insert but returns a boolean and the iterator it is
  //equal to the indexes string value
  for(int i = ascValue; i < m_htSize; i++)
    {
      set<string>::iterator it = m_ht[i].find(line);
      if(*it == line)
	return true;
    }
  for(int i = 0; i < ascValue; i++)
    {
      set<string>::iterator it = m_ht[i].find(line);
      return true;
    }
  return false;
}

// If 'line' is in the the hash table, return its set of anagrams,
// including 'line'.  If 'line' is not in the hash table, return an
// emtpy set of strings.
set<string> Anahash::getAnagrams(string line)
{
  //same as search but returns the index of the hash table
  unsigned int ascValue = anaHash(line);
  for(int i = ascValue; i < m_htSize; i++)
    {
      set<string>::iterator it = m_ht[i].find(line);
      if(*it == line)
	return m_ht[i];
    }
  for(int i = 0; i < ascValue; i++)
    {
      set<string>::iterator it = m_ht[i].find(line);
      if(*it == line)
	return m_ht[i];
    }
}

// Dump all non-empty lists from the hash table.  Print the hash
// value in hexadecimal and the strings in the list.
void Anahash::dump()
{
  for(int i = 0; i < m_htSize; i++)
    {
      //outputs the anagrams
      if(m_ht[i].empty() == false)
	{
	  cout << hex << anaHash(*m_ht[i].begin()) << endl;
	}
      for(set<string>::iterator it = m_ht[i].begin(); it != m_ht[i].end(); ++it)
	{
	  if(m_ht[i].empty() == false)
	    cout << "\t" << *it << endl;
	}
    }
}

//used from the data stucture book; page 379
unsigned int Anahash::anaHash(string line)
{
  unsigned int h = 0;
  for (unsigned int i = 0; i < line.length(); i++)
    {
      h += (unsigned int) line[i]; // add in next character
    }
  h = (h << 5) | (h >> 27); // 5-bit cyclic shift
  return h;
}

//checks to see if the line is an anagram
bool Anahash::isAnagram(string s1, string s2)
{
  int a = s1.length();
  int b = s2.length();

  // If length of the strings are not equal, then they are not an anagram
  if (a != b)
    return false;

  // Sort both the strings
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());

  // Compares the sorted strings
  for (int i = 0; i < a; i++)
    if (s1[i] != s2[i])
      return false;
  
  return true;
}
