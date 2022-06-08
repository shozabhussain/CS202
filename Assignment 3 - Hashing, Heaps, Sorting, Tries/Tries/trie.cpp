#ifndef __TRIE_CPP
#define __TRIE_CPP
#include<string>
#include<iostream>

#include "trie.hpp"

using namespace std;

trie::trie()
{
    root = shared_ptr<Node>(new Node); root->value = ' ';
}

void trie::insertWord(string word)
{
    shared_ptr<Node> temp = root ;

    for(int i=0; i<word.length(); i++)
    {
        // at each iteration inserts one charactor of the word, starting from the first
        shared_ptr<Node> charToInsert = shared_ptr<Node>(new Node); charToInsert -> value = word[i] ;

        if(temp ->children.size() == 0)
        {
            temp -> children.push_back(charToInsert) ;
            temp = temp -> children[ temp -> children.size()-1 ] ;
            continue ;
        }

        int index = findChar(temp ->children, word[i]) ;

        // if character is not found then go into this if statement
        if( index == -1 )
        {
            bool inserted = false ;

            // inserts the character in sorted order
            for(int j=0 ; j< temp->children.size(); j++)
            {
                if( word[i] > temp -> children[j] -> value)
                {
                    continue ;
                }
                else
                {
                    temp -> children.insert( temp ->children.begin()+j, charToInsert);
                    temp = temp -> children[j] ;
                    inserted = true ;
                    break ;
                }
            }

            // if the character is still not inserted then the children vector was empty so insert it as the first child
            if(inserted == false)
            {
                temp -> children.push_back(charToInsert) ;
                temp = temp -> children[ temp -> children.size()-1 ] ;
                continue ;
            }
        }
        else
        {
            // else it is present so move on to next iteration
            temp = temp -> children[index] ;
            continue ;
        }
    }
}

bool trie::search(string word)
{
    shared_ptr<Node> temp = root ;
    bool found = true ;

    for(int i=0; i<word.length(); i++)
    {
        int index = findChar(temp ->children, word[i]) ;

        if(index == -1)
        {
            // if any of the character of word not found then return false
            return false ;
        }
        else
        {
            temp = temp -> children[index] ;
        }
    }

    return true ;
}

string trie::longestSubstr(string word)
{
    // similar to search but only difference is that it will not return false upon failing to find the character
    // instead it will concetenate all the characters found uptill now and return the substr
    string longest = "" ;
    shared_ptr<Node> temp = root ;

    for(int i=0; i<word.length(); i++)
    {
        int index = findChar(temp ->children, word[i]) ;

        if(index == -1)
        {
            return longest ;
        }
        else
        {
            longest = longest + word[i] ;
            temp = temp -> children[index] ;
        }
    }

    return longest ;
}

vector<string> trie::getTrie()
{
    vector<string> resultantVector ;

    getTrieHelper(root, "", resultantVector ) ;

    return resultantVector ;
}

void trie::deleteWord(string word)
{
    while(1)
    {
        shared_ptr<Node> temp = root ;

        for(int i=0; i< word.size(); i++)
        {
            int index = findChar(temp -> children, word[i]) ;

            if(index == -1)
            {
                return ;
            }

            if(temp -> children[index] -> children.size() == 0)
            {
                temp -> children.erase( temp ->children.begin() + index ) ;
                break;
            }
            else
            {
                temp = temp -> children[index] ;
            }
        }

        if(word.length() == 1)
        {
            return ;
        }

        // deletes the last character of the word after each iteration until word length is 1
        word = word.substr(0, word.length()-1 ) ;
    }
}

void trie::getTrieHelper(shared_ptr<Node> root, string x, vector<string> &v)
{
    shared_ptr<Node> temp = root ;

    // if leaf node is reached then the word is complete so store the concentenated string of characters in the vector
    if(temp ->children.size() == 0)
    {
        v.push_back(x) ;
        return ;
    }

    // else go deeper
    for(int i=0; i<temp ->children.size(); i++)
    {
        string s = x + temp -> children[i] ->value ;
        getTrieHelper(temp ->children[i], s, v) ;
    }
}

int trie::findChar(vector<shared_ptr<Node>> children, char x)
{
    for(int i=0; i<children.size(); i++)
    {
        if(children[i] ->value == x)
        {
            return i ;
        }
    }

    // return -1 if character is not found
    return -1 ;
}

#endif