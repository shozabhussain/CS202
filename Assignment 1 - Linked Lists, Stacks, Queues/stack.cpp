#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
    this -> list = otherStack.list ;
}

template <class T>
Stack<T>::~Stack()
{
    while( this -> list.getHead() != NULL )
    {
        this -> list.deleteHead() ;
    }
}

template <class T>
void Stack<T>::push(T item)
{
   this -> list.insertAtHead(item) ;
}

template <class T>
T Stack<T>::top()
{
    return this -> list.getHead() -> value ;
}

template <class T>
T Stack<T>::pop()
{
    if(this ->isEmpty())
    {
        return NULL ;
    }
    else 
    {
        T pop = this -> list.getHead() -> value ;
        this -> list.deleteHead() ;
        return pop ;
    }
    
}

template <class T>
int Stack<T>::length()
{
    return this -> list.length() ;
}

template <class T>
bool Stack<T>::isEmpty()
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
