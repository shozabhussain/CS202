#ifndef __TREE_CPP
#define __TREE_CPP

#include "tree.hpp"

// Constructor
template <class T, class S>
Tree<T,S>::Tree(shared_ptr<node<T,S>> root) {
	this->root = root;
}

// This function finds a key in the tree and returns the respective node
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKey(T key) {

	shared_ptr<node<T,S>> temp ;
	temp = this -> root ;
	return findKeyHelper(temp, key);
}

// Helper function to find a key in the tree
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKeyHelper(shared_ptr<node<T,S>> currNode, T key) {

	if (currNode == NULL)
	{
 		return NULL ;
	}
	else if(currNode -> key == key)
	{
		shared_ptr<node<T,S>> temp = currNode ;
		return temp ;
	}

	shared_ptr<node<T,S>> temp2 =  findKeyHelper(currNode -> child, key) ;

	if (temp2 != NULL)
	{
		return temp2 ;
	}
	else
	{
		return findKeyHelper(currNode -> sibling, key) ;
	}
}

// This function inserts a the given node as a child of the given key
template <class T, class S>
bool Tree<T,S>::insertChild(shared_ptr<node<T,S>> c, T key) {

	shared_ptr<node<T,S>> temp ;
	temp = findKey(c -> key) ;

	if ( temp == NULL)
	{
		shared_ptr<node<T,S>> temp2 ;
		temp2 = findKey(key) ;

		if(temp2 == NULL )
		{
			return false ;
		}
		else if ( temp2 -> child == NULL)
		{
			temp2 -> child = c ;
			return true ;
		}
		else
		{
			temp2 = temp2 -> child ;
			if(temp2 -> sibling == NULL)
			{
				temp2 -> sibling = c;
				return true ;
			}

			while(temp2 -> sibling != NULL)
			{
				temp2 = temp2 -> sibling ;
			}

			temp2 -> sibling = c ;
			return true ;

		}
	}
	else
	{
		return false ;
	}

}

// This function returns all the children of a node with the given key
template <class T, class S>
vector<shared_ptr<node<T,S>> > Tree<T,S>::getAllChildren(T key) {

	shared_ptr<node<T,S>> temp ;
	vector<shared_ptr<node<T,S>> > childrenVector ;
	temp = findKey(key) ;

	if (temp == NULL)
	{
		return childrenVector ;
	}
	else if (temp -> child == NULL)
	{
		return childrenVector ;
	}
	else
	{
		temp = temp -> child ;
		while(temp != NULL)
		{
			childrenVector.push_back(temp) ;
			temp = temp -> sibling ;
		}

		return childrenVector ;
	}
}

// This function returns the height of the tree
template <class T, class S>
int Tree<T,S>::findHeight() {
	return findHeightHelper(root)-1;
}

// Helper function to find height of the tree
template <class T, class S>
int Tree<T,S>::findHeightHelper(shared_ptr<node<T,S>> currNode) {

	if (currNode == NULL)
	{
 		return 0 ;
	}

	int temp2 = findHeightHelper(currNode -> child) + 1 ;

	int temp3 =  findHeightHelper(currNode -> sibling) ;

	if(temp3 > temp2)
	{
		return temp3 ;
	}
	else
	{
		return temp2 ;
	}


}

// This function deletes the node of a given key (iff it is a leaf node)
template <class T, class S>
bool Tree<T,S>::deleteLeaf(T key) {

	shared_ptr<node<T,S>> temp ;
	temp = findKey(key) ;

	if (temp == this -> root)
	{
		return false;
	}
	else if (temp == NULL)
	{
		return false ;
	}
	else if( temp -> child == NULL)
	{
		shared_ptr<node<T,S>> temp2 = deleteLeafHelper(this -> root, key) ;

		if (temp2 -> child == temp )
		{
			temp2 -> child = temp -> sibling ;
			return true ;
		}
		else if(temp2 -> sibling == temp)
		{
			temp2 -> sibling = temp -> sibling ;
			return true ;
		}
	}
	else
	{
		return false;
	}

}

// // Helper function to delete lead node
 template <class T, class S>
 shared_ptr<node<T,S>> Tree<T,S>::deleteLeafHelper(shared_ptr<node<T,S>> currNode, T key) {

	if (currNode == NULL)
	{
 		return NULL ;
	}

	shared_ptr<node<T,S>> temp = currNode ;
	currNode = currNode -> child ;

	while(currNode != NULL)
	{
		if(currNode-> key == key)
		{
			return temp ;
		}

		currNode = currNode -> sibling ;
	}

	shared_ptr<node<T,S>> temp2 =  deleteLeafHelper(temp -> child, key) ;

	if (temp2 != NULL)
	{
		return temp2 ;
	}
	else
	{
		return deleteLeafHelper(temp -> sibling, key) ;
	}
}

// This function deletes the tree
template <class T, class S>
void Tree<T,S>::deleteTree(shared_ptr<node<T,S>> currNode) {

	currNode = NULL ;
	return ;
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>>  Tree<T,S>::getRoot() {

	return this -> root ;
}

#endif
