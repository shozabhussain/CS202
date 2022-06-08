#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;
template <class T>
LinkedList<T>::LinkedList()
{
    this -> head = NULL ;
    this -> tail = NULL ;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    if( otherLinkedList.head == NULL)
    {
        return ;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        temp = otherLinkedList.head ;
        while( temp!= NULL)
        {
            this -> insertAtTail(temp -> value ) ;
            temp = temp -> next ;
        }
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    
    if ( this -> head == NULL ) 
    {
        shared_ptr<ListItem<T>> temp(new ListItem<T>(item));
        this -> head = temp ;
        this -> tail = temp ;
        
    } 
    else 
    {
        shared_ptr<ListItem<T>> temp(new ListItem<T>(item));
        temp -> next = this -> head ;
        this -> head -> prev = temp ;
        temp -> prev = NULL ;
        this -> head = temp ;
    }
    
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    if ( this -> head == NULL ) 
    {
        shared_ptr<ListItem<T>> temp(new ListItem<T>(item));
        this -> head = temp ;
        this -> tail = temp ;
    } 
    else 
    {
        shared_ptr<ListItem<T>> temp(new ListItem<T>(item));
        temp -> prev = this -> tail;
        this -> tail -> next = temp ;
        temp -> next = NULL ;
        this -> tail = temp ;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    if(this -> head == NULL)
    {
        return ;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        shared_ptr<ListItem<T>> newItem(new ListItem<T>(toInsert));
        temp = this -> head ; 
        while(temp != NULL)
        {
            if(temp -> value == afterWhat)
            {
                if(temp -> next == NULL)
                {
                    this -> insertAtTail(toInsert) ;
                    return ;
                }
                newItem -> next = temp -> next ;
                temp -> next -> prev = newItem ;
                newItem -> prev = temp ;
                temp -> next = newItem ;
                return ;
            }

            temp = temp -> next ;
        }

        return ;
    }
}


template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
    return this -> head ;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
    return this -> tail ;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
    if(this -> head == NULL)
    {
        return NULL ;
    }
    else
    {
        shared_ptr<ListItem<T>> temp ;
        temp = this -> head ;
        while(temp != NULL)
        {
            if(temp -> value == item)
            {
                return temp ;
            }

            temp = temp -> next ;
        }

        return NULL ;
    }
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    if( this -> head == NULL)
    {
        return ;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        temp = this -> head ;
        while(temp != NULL)
        {
            if(temp -> value == item)
            {
                if(temp -> next == NULL)
                {
                    this -> deleteHead() ;
                    return ;
                }
                else if (temp -> prev == NULL)
                {
                    this -> deleteTail() ;
                    return ;
                }
                temp -> prev -> next = temp -> next ;
                temp -> next -> prev = temp -> prev ;
            }

            temp = temp -> next ;
        }

        return ;
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(this -> head == NULL)
    {
        return ;
    }
    else if(head -> next == NULL)
    {
        head = NULL ;
        return ;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        temp = this -> head ;
        this -> head = temp -> next ;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    if(this -> head == NULL)
    {
        return ;
    }
    else if( tail -> prev == NULL)
    {
        tail = NULL ;
        return ;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        temp = this -> tail ;
        this -> tail = temp -> prev ;
    }
}

template <class T>
int LinkedList<T>::length()
{
    if(this -> head == NULL)
    {
        return 0;
    }
    else 
    {
        shared_ptr<ListItem<T>> temp ;
        temp = this -> head ;
        int len = 0 ;
        while(temp != NULL)
        {
            len++ ;
            temp = temp -> next ;
        }

        return len ;
    }
}

#endif