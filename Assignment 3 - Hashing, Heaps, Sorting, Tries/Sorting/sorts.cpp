#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "LinkedList.cpp"
#include<iostream>
using namespace std ;

//===========================Helper Function Definition================================

shared_ptr<ListItem<long>> sortedMerge(shared_ptr<ListItem<long>> a, shared_ptr<ListItem<long>> b) ;
shared_ptr<ListItem<long>> sort(shared_ptr<ListItem<long>> list, int n) ;
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	long arr[nums.size()];

    for(int i=0; i<nums.size(); i++)
    {
        arr[i] = nums[i] ;
    }

    for (int i = 1; i < nums.size(); i++)
    {
        int currentValue = arr[i];
        int j = 0 ;

        for( j = 0; j < i; j++ )
        {
            // if previous index value is greater than current value then swap it forward and check value of previous of previous index
            //repeat this until value is less or equal to current value and then replace it with current value

            if( arr[i-j-1] > currentValue )
            {
                arr[i-j] = arr[i-j-1] ;
            }
            else
            {
                break ;
            }
        }

        arr[i-j] = currentValue ;
    }

    for(int i=0; i<nums.size(); i++)
    {
        nums[i] = arr[i] ;
    }

    return nums ;
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
    LinkedList<long> list ;

    for(int i=0; i<nums.size(); i++)
    {
        list.insertAtHead(nums[i]) ;
    }

    shared_ptr<ListItem<long>> temp = sort(list.getHead(), nums.size()) ;

    int i =0;
    while(temp != NULL)
    {
        nums[i] = temp -> value ;
        i++ ;
        temp = temp -> next ;
    }

    return nums ;
}

//=====================================================================================

//==============================Helper Functions=======================================

shared_ptr<ListItem<long>> sortedMerge(shared_ptr<ListItem<long>> a, shared_ptr<ListItem<long>> b)
{
    shared_ptr<ListItem<long>> list = NULL ;

    if(a == NULL or b == NULL)
    {
        if(a == NULL)
        {
            return b ;
        }
        else
        {
            return a ;
        }
    }

    // stores the smallest value from the two lists and pass the lists again but this time excluding the value that is already stored
    else if(a -> value < b -> value)
    {
        list = a ;
        list -> next = sortedMerge(a ->next, b) ;
    }

    else
    {
        list = b ;
        list -> next = sortedMerge(a, b ->next) ;
    }

    return list ;
}

shared_ptr<ListItem<long>> sort(shared_ptr<ListItem<long>> list, int n)
{
    if(n == 1)
    {
        return list ;
    }

    int middle = n/2  ;
    shared_ptr<ListItem<long>> temp = list ;

    // head to first half of the list
    shared_ptr<ListItem<long>> l1 = list ;
    shared_ptr<ListItem<long>> l2 ;

    for(int i=0; i<middle; i++)
    {
        temp = temp -> next ;
    }

    temp -> prev -> next = NULL ;

    // head to the second half of the list
    l2 = temp ;

    l1 = sort(l1, middle) ;
    l2 = sort(l2, n-middle) ;

    // when both lists are sorted, they are then merged
    return sortedMerge(l1, l2) ;
}

#endif