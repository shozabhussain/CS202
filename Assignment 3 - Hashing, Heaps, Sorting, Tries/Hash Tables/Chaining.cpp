#ifndef CHAINING_CPP
#define CHAINING_CPP

#include "Chaining.h"
#include "HashFunction.cpp"


// Constructor
HashC::HashC(int size)
{
    this -> tableSize = size ;
    hashTable.reset(new LinkedList<string>[size], default_delete<LinkedList<string>[]>()) ;
}


// Destructor
HashC::~HashC()
{
    this -> hashTable = NULL ;
}


// Given a String, return its hash
unsigned long HashC::hash(string input)
{
    return divCompression( bitHash(input), tableSize ) ;
}


// Takes a hash of 'word' and inserts it into hashTable accordingly
void HashC::insertWord(string word)
{
    hashTable.get()[ this -> hash(word) ].insertAtTail(word) ;
}


// Locates 'word' in the hash table and returns a pointer to it
shared_ptr<ListItem<string>> HashC::lookupWord(string word)
{
    return hashTable.get()[ this -> hash(word) ].searchFor(word) ;
}


// Deletes 'word' from the hash table
void HashC::deleteWord(string word)
{
    hashTable.get()[ this -> hash(word) ].deleteElement(word) ;
}

#endif