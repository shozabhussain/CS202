#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <memory>

MinHeap::MinHeap(int cap)
{
	heap_size = 0 ;
	capacity = cap ;
	harr.reset(new int[cap], default_delete<int[]>()) ;
}

int MinHeap::parent(int i)
{
	return (i-1) / 2 ;
}

int MinHeap::left(int i)
{
	return (2*i+1) ;
}

int MinHeap::right(int i)
{
	return (2*i+2) ;
}

int MinHeap::extractMin()
{
	int minValue = harr.get()[0] ;
	this -> deleteKey(0) ;
	return minValue ;
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr.get()[i] = new_val ;

	int child = i ;
	int parent = (child - 1) / 2 ;

	while(child > 0)
	{
		if (harr.get()[child] < harr.get()[parent])
		{
			int temp = harr.get()[child] ;
			harr.get()[child] = harr.get()[parent] ;
			harr.get()[parent] = temp ;

			child = parent ;
			parent = (child - 1) / 2 ;
		}
		else
		{
			break ;
		}
	}
}

int MinHeap::getMin()
{
	return harr.get()[0] ;
}

void MinHeap::deleteKey(int i)
{
	if(i >= heap_size)
	{
		return;
	}
	else if ( i < 0)
	{
		return ;
	}
	else
	{
		harr.get()[i] = harr.get()[heap_size - 1] ;
		heap_size-- ;

		int parentIndex = i ;
		int leftIndex = this -> left(parentIndex) ;
		int rightIndex = this -> right(parentIndex) ;

		// parent should be less than both of the children
		while( harr.get()[parentIndex] > harr.get()[leftIndex] || harr.get()[parentIndex] > harr.get()[rightIndex] )
		{
			// if children doesn't exist in heap then return
			if( leftIndex >= heap_size && rightIndex >= heap_size )
			{
				return ;
			}

			int parentValue = harr.get()[parentIndex] ;

			// filter down
			if( harr.get()[leftIndex] > harr.get()[rightIndex] )
			{
				harr.get()[parentIndex] = harr.get()[rightIndex] ;
				harr.get()[rightIndex] = parentValue ;
				parentIndex = rightIndex ;
			}
			else
			{
				harr.get()[parentIndex] = harr.get()[leftIndex] ;
				harr.get()[leftIndex] = parentValue ;
				parentIndex = leftIndex ;
			}

			// if leaf node reached, can't percolate down further so return
			if(parentIndex == heap_size)
			{
				return ;
			}
			else
			{
				leftIndex = this -> left(parentIndex) ;
				rightIndex = this -> right(parentIndex) ;
			}
		}

		return ;
	}
}

void MinHeap::insertKey(int k)
{

	if(heap_size == capacity)
	{
		return ;
	}

	harr.get()[heap_size] = k ;
	heap_size++ ;

	int child = heap_size - 1 ;
	int parent = (child - 1) / 2 ;

	while(child > 0)
	{
		if (harr.get()[child] < harr.get()[parent])
		{
			int temp = harr.get()[child] ;
			harr.get()[child] = harr.get()[parent] ;
			harr.get()[parent] = temp ;

			child = parent ;
			parent = (child - 1) / 2 ;
		}
		else
		{
			break ;
		}
	}

	return ;
}

shared_ptr<int> MinHeap::getHeap()
{
	return harr;
}

#endif