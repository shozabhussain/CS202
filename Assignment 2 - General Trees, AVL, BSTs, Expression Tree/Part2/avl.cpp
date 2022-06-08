#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include <memory>
#include "avl.hpp"

using namespace std;

// Constructor
template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}

// This function inserts a given node in the tree
template <class T, class S>
void AVL<T,S> :: insertNode(shared_ptr<node<T,S>> newNode){

    if(this -> root == NULL)
    {
        root = newNode ;
    }
    else
    {
        shared_ptr<node<T,S>> temp = this -> root ;

        while(1)
        {
            if(newNode -> key > temp -> key)
            {
                if(temp -> right == NULL)
                {
                    temp -> right = newNode ;

                    if(temp == this -> root)
                    {
                        return ;
                    }
                    break ;
                }
                else
                {
                    temp = temp -> right ;
                }
            }
            else if(newNode -> key < temp -> key)
            {
               if(temp -> left == NULL)
                {
                    temp -> left = newNode ;
                    if(temp == this -> root)
                    {
                        return ;
                    }
                    break ;
                }
                else
                {
                    temp = temp -> left ;
                }
            }
        }

        if(isAVL)
        {
            shared_ptr<node<T,S>> x = searchNode(newNode -> key) ;

            while(1)
            {
                if(height(temp -> left) - height(temp -> right) > 1 || height(temp -> left) - height(temp -> right) < -1)
                {
                    break ;
                }
                else
                {
                    temp = deleteLeafHelper(this -> root, temp -> key) ;

                    if(temp == NULL)
                    {
                        return ;
                    }
                    continue ;
                }
            }

            shared_ptr<node<T,S>> z = temp ;
            shared_ptr<node<T,S>> y ;

            if( height(z -> left ) > height( z-> right) )
            {
                y = z -> left ;
            }
            else
            {
                y = z -> right ;
            }

            if( height(y -> left ) > height( y-> right) )
            {
                x = y -> left ;
            }
            else
            {
                x = y -> right ;
            }

            if( z -> left == y && y -> left == x)
            {
                if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
                {
                    this -> root = rotateRight(z) ;
                }
                else
                {
                    if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                    {
                        deleteLeafHelper(this -> root, z -> key) -> right = rotateRight(z) ;
                    }
                    else
                    {
                        deleteLeafHelper(this -> root, z -> key) -> left = rotateRight(z) ;
                    }
                }
                return ;
            }
            else if(z -> right == y && y -> right == x)
            {
                if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
                {
                    this -> root = rotateLeft(z) ;
                }
                else
                {
                    if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                    {
                        deleteLeafHelper(this -> root, z -> key) -> right = rotateLeft(z) ;
                    }
                    else
                    {
                        deleteLeafHelper(this -> root, z -> key) -> left = rotateLeft(z) ;
                    }
                }
                return ;
            }
            else if(z -> left == y && y -> right == x)
            {

               z -> left = rotateLeft(y) ;

                if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
                {
                    this -> root = rotateRight(z) ;
                }
                else
                {
                    if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                    {
                        deleteLeafHelper(this -> root, z -> key) -> right = rotateRight(z) ;
                    }
                    else
                    {
                        deleteLeafHelper(this -> root, z -> key) -> left = rotateRight(z) ;
                    }
                }
                return ;
            }
            else if(z -> right == y && y -> left == x)
            {

               z -> right = rotateRight(y) ;

                if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
                {
                    this -> root = rotateLeft(z) ;
                }
                else
                {
                    if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                    {
                        deleteLeafHelper(this -> root, z -> key) -> right = rotateLeft(z) ;
                    }
                    else
                    {
                        deleteLeafHelper(this -> root, z -> key) -> left = rotateLeft(z) ;
                    }
                }
                return ;
            }
        }
        else
        {
            return ;
        }
    }
}

// This function searches a node in a tree by its key
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: searchNode(T k){

    if(this -> root -> key == k)
    {
        return this -> root ;
    }
    else
    {
        shared_ptr<node<T,S>> temp = this -> root ;

        while(1)
        {
            if(k > temp -> key && temp -> right != NULL)
            {
                if( temp -> right -> key == k )
                {
                    return temp -> right ;
                }
                else
                {
                    temp = temp -> right ;
                    continue ;
                }
            }
            else if( k < temp -> key && temp -> left != NULL)
            {
                if( temp -> left -> key == k )
                {
                    return temp -> left ;
                }
                else
                {
                    temp = temp -> left ;
                    continue ;
                }
            }

            return NULL ;
        }
    }
}

// This function deletes a given node from the tree
template <class T, class S>
void AVL<T,S>::deleteNode(T k){

    if(!isAVL)
    {
        deleteNodeHelper(this -> root, k) ;
        return ;
    }

    if(this -> root -> left == NULL && this -> root -> right == NULL)
    {
        this -> root = NULL ;
        return ;
    }

    shared_ptr<node<T,S>> temp ;

    if( this -> root -> key == k )
    {
        deleteNodeHelper(root, k) ;
        temp = this -> root ;
    }
    else
    {
        temp = deleteLeafHelper(this -> root, k) ;
        deleteNodeHelper(root, k) ;
    }

    while(1)
    {
        while(1)
        {
            if(height(temp -> left) - height(temp -> right) > 1 || height(temp -> left) - height(temp -> right) < -1)
            {
                break ;
            }
            else
            {
                temp = deleteLeafHelper(this -> root, temp -> key) ;
                if(temp == NULL)
                {
                    return ;
                }
                continue ;
            }
        }

        shared_ptr<node<T,S>> z = temp ;
        shared_ptr<node<T,S>> y ;
        shared_ptr<node<T,S>> x ;

        if( height(z -> left ) > height( z-> right) )
        {
            y = z -> left ;
        }
        else
        {
            y = z -> right ;
        }

        if( height(y -> left ) > height( y-> right) )
        {
            x = y -> left ;
        }
        else
        {
            x = y -> right ;
        }

        if( z -> left == y && y -> left == x)
        {
            if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
            {
                this -> root = rotateRight(z) ;
                continue ;
            }
            else
            {
                if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                {
                    deleteLeafHelper(this -> root, z -> key) -> right = rotateRight(z) ;
                    continue ;
                }
                else
                {
                    deleteLeafHelper(this -> root, z -> key) -> left = rotateRight(z) ;
                    continue ;
                }
            }
        }
        else if(z -> right == y && y -> right == x)
        {
            if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
            {
                this -> root = rotateLeft(z) ;
                continue ;
            }
            else
            {
                if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                {
                    deleteLeafHelper(this -> root, z -> key) -> right = rotateLeft(z) ;
                    continue ;
                }
                else
                {
                    deleteLeafHelper(this -> root, z -> key) -> left = rotateLeft(z) ;
                     continue ;
                }
            }
        }
        else if(z -> left == y && y -> right == x)
        {
            z -> left = rotateLeft(y) ;

            if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
            {
                this -> root = rotateRight(z) ;
                 continue ;
            }
            else
            {
                if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                {
                    deleteLeafHelper(this -> root, z -> key) -> right = rotateRight(z) ;
                     continue ;
                }
                else
                {
                    deleteLeafHelper(this -> root, z -> key) -> left = rotateRight(z) ;
                     continue ;
                }
            }
        }

        else if(z -> right == y && y -> left == x)
        {
            z -> right = rotateRight(y) ;

            if( (deleteLeafHelper(this -> root, z-> key)) == NULL )
            {
                this -> root = rotateLeft(z) ;
                 continue ;
            }
            else
            {
                if ( deleteLeafHelper(this -> root, z -> key) -> right == z )
                {
                    deleteLeafHelper(this -> root, z -> key) -> right = rotateLeft(z) ;
                     continue ;
                }
                else
                {
                    deleteLeafHelper(this -> root, z -> key) -> left = rotateLeft(z) ;
                     continue ;
                }
            }
        }
    }
    return ;
}

// This function helps delete a given node from the tree
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::deleteNodeHelper(shared_ptr<node<T,S>> root, T k){

    shared_ptr<node<T,S>> nodeToDelete = root;
    shared_ptr<node<T,S>> parent = NULL;

    while ( nodeToDelete != NULL )
    {
        if( nodeToDelete -> key == k )
        {
            break ;
        }
        else
        {
            parent = nodeToDelete;

            if ( nodeToDelete->key > k )
            {
                nodeToDelete = nodeToDelete->left;
            }
            else
            {
                nodeToDelete = nodeToDelete->right;
            }
        }
    }

    if (nodeToDelete == NULL)
    {
        return root;
    }

    if (nodeToDelete -> right == NULL || nodeToDelete -> left == NULL)
    {
       shared_ptr<node<T,S>> newnodeToDelete;

        if (nodeToDelete -> right == NULL)
        {
            newnodeToDelete = nodeToDelete -> left;
        }
        else if(nodeToDelete -> left == NULL)
        {
            newnodeToDelete = nodeToDelete -> right;
        }

        if (parent == NULL)
        {
            return newnodeToDelete;
        }
        else
        {
            if (nodeToDelete == parent -> right)
            {
                parent -> right = newnodeToDelete;
            }
            else
            {
                parent -> left = newnodeToDelete;

            }
        }
    }
    else
    {
        shared_ptr<node<T,S>> parentRightSmallest = NULL ;
        shared_ptr<node<T,S>> rightSmallest;
        rightSmallest = nodeToDelete -> right;

        while (rightSmallest -> left != NULL)
        {
            parentRightSmallest = rightSmallest;
            rightSmallest = rightSmallest -> left;
        }

        if (parentRightSmallest == NULL)
        {
            nodeToDelete->right = rightSmallest ->right;
        }
        else
        {
            parentRightSmallest -> left = rightSmallest -> right;
        }

        nodeToDelete->key = rightSmallest->key;
    }
    return root;
}

// This function gives the parent of the node
 template <class T, class S>
 shared_ptr<node<T,S>> AVL<T,S>::deleteLeafHelper(shared_ptr<node<T,S>> root, T k) {

    if(this -> root -> key == k)
    {
        return NULL ;
    }
    else
    {
        shared_ptr<node<T,S>> temp = this -> root ;

        while(1)
        {
            if(k > temp -> key && temp -> right != NULL)
            {
                if( temp -> right -> key == k )
                {
                    return temp  ;
                }
                else
                {
                    temp = temp -> right ;
                    continue ;
                }
            }
            else if( k < temp -> key && temp -> left != NULL)
            {
                if( temp -> left -> key == k )
                {
                    return temp  ;
                }
                else
                {
                    temp = temp -> left ;
                    continue ;
                }
            }
            return NULL ;
        }
    }
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::getRoot(){
    return root;
}

// This function calculates and returns the height of the tree
template <class T, class S>
int AVL<T,S> :: height (shared_ptr<node<T,S>> p){

    if( p == NULL)
    {
        return 0 ;
    }
    else if(p -> right == NULL && p -> left == NULL)
    {
        return 1 ;
    }
    else
    {
        return findHeightHelper(p) ;
    }
}

template <class T, class S>
int  AVL<T,S>::findHeightHelper(shared_ptr<node<T,S>> nodeToDeleteNode) {

	if (nodeToDeleteNode == NULL)
	{
 		return 0 ;
	}

	int temp2 = findHeightHelper(nodeToDeleteNode -> left) + 1 ;
	int temp3 =  findHeightHelper(nodeToDeleteNode -> right) + 1 ;

	if(temp3 > temp2)
	{
		return temp3 ;
	}
    else
    {
        return temp2 ;
    }
}

template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::rotateLeft(shared_ptr<node<T,S>> root) {

    shared_ptr<node<T,S>> temp = root -> right -> left ;
    shared_ptr<node<T,S>> newRoot = root -> right ;
    newRoot -> left = root ;
    root -> right = temp ;
    return newRoot ;
}
template <class T, class S>
shared_ptr<node<T,S>>  AVL<T,S>::rotateRight(shared_ptr<node<T,S>> root) {

    shared_ptr<node<T,S>> temp = root -> left -> right ;
    shared_ptr<node<T,S>> newRoot = root -> left ;
    newRoot -> right = root ;
    root -> left = temp ;
    return newRoot ;
}
#endif