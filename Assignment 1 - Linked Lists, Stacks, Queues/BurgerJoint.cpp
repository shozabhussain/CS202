#ifndef BurgerJoint_CPP
#define BurgerJoint_CPP
#include "BurgerJoint.h"
#include <iostream>
#include <fstream>
using namespace std;

/*
    Helper function to tell whether the 
    given string is a number or not 
*/
bool isNumber(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if( !(isdigit((unsigned char)str[i])) )
        {
            return false;
        }
        
    }

    return true;
}


/*
    Constructor:
    1. Load topping priority from topping_priority.txt into
       topping_priority attribute
    2. Load every customers' unsorted toppings form 
       assembly line - load data from assembly.txt 
       into customers queue
    
    For you convenience this has been done!
*/
BurgerJoint::BurgerJoint()
{
   
    ifstream fin("topping_priority.txt");

    string line;

    int count = 0;

    while (getline (fin, line)) 
    {

        topping_priority[count] = line;
        count++;

    }

    //saving number of toppings
    number_of_toppings = count;

    fin.close();
    
    //loading customers' unsorted toppings from assembly line
    fin.open("assembly.txt");


    bool first_line = true;

    int total_customers;
    int cust_id;

    LinkedList<string> lines;

    //reading all lines
    while(getline (fin, line))
    {
        lines.insertAtTail(line);
    }

    fin.close();

    shared_ptr<ListItem<string>> ptr = lines.getHead();

    ptr = lines.getHead();

    //adding customers with correct id and toppings into
    //customers queue
    while(ptr != NULL)
    {
        line = ptr->value;
        if(first_line)
        {
            //noting down total customers
            total_customers = stoi(line);
            first_line = false;
            ptr = ptr -> next;
        }

        else
        {
            //noting down customer id
            cust_id = stoi(line);

            ptr = ptr->next;

            shared_ptr<customer> new_cust(new customer);
            new_cust->id = cust_id;

            //noting down customer unsorted toppings
            while(ptr != NULL)
            {  
                line = ptr->value;
                if(isNumber(ptr->value))
                {
                    break;
                }
                new_cust->order.push(line);
                ptr = ptr->next;
            }

            //enqueuing customer
            customers.enqueue(new_cust);
        }
        
    }

}


/*
    Function to fetch priority of a topping.
    Matches prioirity from topping_priority list.
*/
int BurgerJoint::getPriority(string item)
{

    for(int i=0; i<number_of_toppings; i++)
    {
        if(topping_priority[i] == item)
        {
            return i ;
        }
    }
}

//destructor
BurgerJoint::~BurgerJoint()
{}

/*
    You have two stacks:
    1. unsorted_toppings
    2. temp_stack

    You have one variable:
    1. temp

    DONOT CREATE ANYMORE VARIABLES OR DATASTRUCTURES IN THIS FUNCTION

    Use the above mentioned variable and datastructures to sort the
    unsorted_toppings stack.
    You need to sort it according to "topping_priority"
*/

Stack<string> temp_stack ;

void BurgerJoint::assemble(Stack<string> &unsorted_toppings)
{
    
    string temp = "empty" ;

    while(unsorted_toppings.length() != 0)
    {
        temp_stack.push(unsorted_toppings.pop()) ;
    }

    for(int i=0; i<number_of_toppings; i++)
    {
        for(int j=temp_stack.length(); j>0; j--)
        { 
            if(temp_stack.top() == topping_priority[number_of_toppings-1-i])
            { 
                temp = temp_stack.pop() ;
            }
            else 
            {
                unsorted_toppings.push(temp_stack.pop()) ;
            }
        }

        if(temp != "empty")
        {
            temp_stack.push(temp) ;
            temp = "empty" ;

            for(int k=unsorted_toppings.length(); k>0; k--)
            {
                temp_stack.push(unsorted_toppings.pop()) ;
            }
        }
        else 
        {
             for(int k=unsorted_toppings.length(); k>0; k--)
            {
                temp_stack.push(unsorted_toppings.pop()) ;
            }
        }
    }

    while(temp_stack.length() !=0)
    {
        unsorted_toppings.push(temp_stack.pop()) ;
    }
}

/*
    Generate an output file similar to assembly.txt.
    The toppings need to be in a sorted order in this file.
    Moreover, every customer needs to hace the correct toppings.

    NAME THE OUTPUT TEXT FILE takeaway.txt
*/
void BurgerJoint::generateOutput()
{
    ofstream MyFile("takeaway.txt");
    MyFile << customers.length() << "\n" ;
    while( customers.length() != 0)
    {
        shared_ptr<customer> c = customers.dequeue();
        MyFile << c -> id << "\n" ;
        while( c -> order.length() != 0)
        {
            MyFile << c -> order.pop() << "\n" ;
        }
    }

    MyFile.close();

}

void BurgerJoint::takeawayCounter()
{
    for(int i=customers.length(); i>0; i--)
    {
        shared_ptr<customer> c = customers.dequeue() ;
        assemble(c -> order) ;
        customers.enqueue(c) ;
    }

    generateOutput() ;
}




#endif

// int main()
// {
//     BurgerJoint b ;
//     Stack<string> unsorted ;
//     unsorted.push("bbun") ;
//     unsorted.push("pickles") ;
//     unsorted.push("tbun") ;
//     unsorted.push("chipotle") ;
//     unsorted.push("patty") ;
//     unsorted.push("mayo") ;
//     unsorted.push("ketchup") ;
//     unsorted.push("onions") ;
//     unsorted.push("lettuce") ;

//     b.assemble(unsorted) ;

//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;
//     cout << unsorted.pop() << endl;


// }