#ifndef LUCKYDRAW_CPP
#define LUCKYDRAW_CPP
#include "luckyDraw.h"
#include "stack.cpp"
#include "queue.cpp"
#include<iostream>
using namespace std ;

luckyDraw::luckyDraw(int count)
{
    totalCount = count ;
}

//populate lane_1 with the given array of winnersId   
void luckyDraw::populateQueue(int* winnersId)
{
    for(int i=0; i<totalCount; i++)
    {
        lane_1.enqueue(winnersId[i]) ;
    }

}

//populate table_1 with the given array of giftsId   
void luckyDraw::populateTable(int* giftsId)
{
    for(int i=0; i<totalCount; i++)
    {
        table_1.push(giftsId[i]) ;
    }
}

//reverse the queue keeping the conditions in mind
void luckyDraw::reverseQueue()
{
    for(int i=0; i<totalCount-1; i++)
    {
       lane_2.enqueue(lane_1.dequeue()) ;
    }

    while(lane_2.length() != 0)
    {
        for(int j=0; j<lane_2.length()-1; j++)
        {
            lane_2.enqueue(lane_2.dequeue()) ;
        }

        lane_1.enqueue(lane_2.dequeue()) ;
    }
}

//transfer the stack keeping the conditions in mind
void luckyDraw::transferStack()
{
    for(int i=0; i<totalCount-1; i++)
    {
        specialVariable = table_1.pop() ;
        for(int j=0; j<totalCount-1-i; j++)
        {
            table_2.push(table_1.pop()) ;
        }

        table_1.push(specialVariable) ;

        for(int k=0; k<totalCount-1-i; k++)
        {
            table_1.push(table_2.pop()) ;
        }
    }

    for(int i=0; i<totalCount; i++)
    {
        table_2.push(table_1.pop()) ;
    }
    

}

void luckyDraw::print()
{
    for(int i=0; i<totalCount; i++)
    {
        cout << table_2.pop() << endl;
    }
}

#endif

// int main()
// {
//     int arr[5] = {1,2,3,4,5} ;
//     luckyDraw l(5) ;
//     l.populateTable(arr) ;
//     l.transferStack() ;
//     l.print();
// }