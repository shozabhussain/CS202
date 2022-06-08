#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "LinearProbing.h"
#include "HashFunction.cpp"
#include <memory>

// Constructor
HashL::HashL(int size)
{
    this -> tableSize = size ;

    for(unsigned long i=0; i<size; i++ )
    {
        shared_ptr<tableItem> temp = make_shared<tableItem>(i, "") ;
        hashTable.push_back(temp) ;
    }
}

// Destructor
HashL::~HashL()
{
    this -> hashTable.clear() ;
}

// Computes the key corresponding to the value.
unsigned long HashL::hash(string value)
{
    return divCompression( bitHash(value), tableSize ) ;
}

// Function to resize the hash table
void HashL::resizeTable()
{
    this -> tableSize = this ->  tableSize*50 ;
    vector<shared_ptr<tableItem>> newHashTable;

    for(unsigned long i=0; i<tableSize; i++ )
    {
        shared_ptr<tableItem> temp = make_shared<tableItem>(i, "") ;
        newHashTable.push_back(temp) ;
    }

    int j = 0 ;

    for(unsigned long i=0; i<tableSize/50; i++)
    {
        if(hashTable[i] -> value != "")
        {
            unsigned long hashKey = hash(hashTable[i] -> value) ;

            unsigned long k = 0 ;
            while(1)
            {
                if(newHashTable[hashKey] -> value == "")
                {
                    newHashTable[hashKey] -> value = hashTable[i] -> value ;
                    j++ ;
                    break ;
                }
                else
                {
                    hashKey = divCompression(hashKey+1, tableSize) ;
                }

                k++ ;
            }

        }

        if(j == count)
        {
            break ;
        }
    }

    hashTable = newHashTable ;
}

// Takes the hash of 'value' and insert it into the hash table
void HashL::insertWord(string value)
{
    unsigned long hashKey = hash(value) ;

    unsigned long i = 0 ;
    while(1)
    {
        if(hashTable[hashKey] -> value == "")
        {
            hashTable[hashKey] -> value = value ;
            count++ ;
            break ;
        }
        else
        {
            hashKey = divCompression(hashKey+1, tableSize) ;
        }

        i++ ;
    }

    if( count / (double)tableSize >= 0.5)
    {
        resizeTable();
    }
}

// Deletes 'value' from the hash table.
void HashL::deleteWord(string value)
{
    unsigned long hashKey = hash(value) ;

    unsigned long i = 0 ;
    while(1)
    {
        if(hashTable[hashKey] -> value == value )
        {
            hashTable[hashKey] -> value = "" ;
            hashTable[hashKey] -> key = -99 ;
            break ;
        }
        else
        {
            hashKey = divCompression(hashKey+1, tableSize) ;
        }

        i++ ;
    }
}

// Locates value in the hash table and returns a pointer to it
shared_ptr<tableItem> HashL::lookupWord(string value)
{
    unsigned long hashKey = hash(value) ;

    unsigned long i = 0 ;
    while(1)
    {
        if(hashTable[hashKey] -> value == value )
        {
            return hashTable[hashKey] ;
        }
        else if(hashTable[hashKey] -> value == "" && hashTable[hashKey] -> key != -99)
        {
            return NULL ;
        }
        else
        {
            hashKey = divCompression(hashKey+1, tableSize) ;
        }

        i++ ;
    }
}

#endif
