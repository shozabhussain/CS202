#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
    this -> list = otherQueue.list ;
}

template <class T>
Queue<T>::~Queue()
{
    while( this -> list.getHead() != NULL )
    {
        this -> list.deleteHead() ;
    }
}

template <class T>
void Queue<T>::enqueue(T item)
{
    this -> list.insertAtTail(item) ;
}

template <class T>
T Queue<T>::front()
{
   T front = this -> list.getHead() -> value ;
   return front ;
}

template <class T>
T Queue<T>::dequeue()
{
    if(this ->isEmpty())
    {
        return NULL ;
    }
    else 
    {
        T dequeue = this -> list.getHead() -> value ;
        this -> list.deleteHead() ;
        return dequeue ;
    }
}

template <class T>
int Queue<T>::length()
{
    return this -> list.length() ;
}

template <class T>
bool Queue<T>::isEmpty()
{
    if(this -> list.length() == 0)
    {
        return true ;
    }
    else 
    {
        return false ;
    }
}


#endif
