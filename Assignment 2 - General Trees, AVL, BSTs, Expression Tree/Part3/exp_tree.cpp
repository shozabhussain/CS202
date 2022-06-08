#ifndef __EXP_TREE_CPP
#define __EXP_TREE_CPP

#include "exp_tree.hpp"
#include<string>
#include<string.h>
#include<strings.h>
#include<bits/stdc++.h>

// class constructor that calls buildTree()
ExpTree::ExpTree(string postfix_exp, bool optimal) {
    buildTree(postfix_exp, optimal);
}

// returns the constructed expression tree from the given postfix expression
// when the optimal argument is set, the subtrees not containing any variables are computed and their result is stored in the tree as only one node
void ExpTree::buildTree(string postfix_exp, bool optimal)
{
    if(postfix_exp == "")
    {
        this -> root = NULL ;
        return ;
    }

    stack<shared_ptr<node>> stack ;

    for(int i=0; i<postfix_exp.length(); i++)
    {
        if( !checkOperator(postfix_exp[i]) )
        {
            shared_ptr<node> newTree = make_shared<node>(postfix_exp[i]) ;
            stack.push(newTree) ;
            continue ;
        }
        else if(stack.size() >= 2)
        {
            shared_ptr<node> t1 = stack.top() ;
            stack.pop() ;
            shared_ptr<node> t2 = stack.top() ;
            stack.pop() ;

            shared_ptr<node> newTree = make_shared<node>(postfix_exp[i]) ;

            if(optimal && isdigit(t1 ->op) && isdigit(t2 -> op) )
            {
                if(postfix_exp[i] == '+')
                {
                    int n1 = (t1 -> op) - 48;
                    int n2 = (t2 -> op) - 48 ;
                    int ans = n1 + n2 ;
                    newTree -> op = ans + '0' ;
                    stack.push(newTree) ;
                }
                else if(postfix_exp[i] == '*')
                {
                    int n1 = (t1 -> op) - 48;
                    int n2 = (t2 -> op) - 48 ;
                    int ans = n1 * n2 ;
                    newTree -> op = ans + '0' ;
                    stack.push(newTree) ;
                }
                else if(postfix_exp[i] == '-')
                {
                    int n1 = (t1 -> op) - 48;
                    int n2 = (t2 -> op) - 48 ;
                    int ans = n2 - n1 ;
                    newTree -> op = ans + '0' ;
                    stack.push(newTree) ;
                }
                else if(postfix_exp[i] == '/')
                {
                    int n1 = (t1 -> op) - 48;
                    int n2 = (t2 -> op) - 48 ;
                    int ans = n2 / n1 ;
                    newTree -> op = ans + '0' ;
                    stack.push(newTree) ;
                }
            }
            else
            {
                newTree ->right = t1 ;
                newTree -> left = t2;
                stack.push(newTree) ;
            }
        }
    }

    this -> root = stack.top() ;
    stack.pop() ;
    return;
}

// returns the root node of the tree;
shared_ptr<node> ExpTree::getRoot()
{
    return root;
}

// returns the value of the expression given the value of the variables in the vector
double ExpTree::calculate(vector<Variable> variables)
{
    if(root == NULL)
    {
        return -99 ;
    }
    if( isdigit(root -> op) )
    {
        double ans = (root -> op) - 48 ;
        return ans ;
    }

    double finalans = calculateRecurse(root, variables) ;
	return finalans ;
}

// recursive function called by calculate():
double ExpTree::calculateRecurse(shared_ptr<node> currNode, vector<Variable> variables)
{
    double leftValue ;
    double rightValue ;

    if(currNode -> left == NULL && currNode -> right == NULL)
    {
        if( !isdigit(currNode -> op) && !checkOperator(currNode -> op))
        {
            return getVal(currNode -> op , variables) ;
        }
        else
        {
            double ans = (currNode -> op) - 48 ;
            return ans ;
        }
    }

    leftValue = calculateRecurse(currNode -> left, variables) ;
    rightValue = calculateRecurse(currNode -> right, variables) ;

    if(currNode -> op == '+')
    {
        double ans = leftValue + rightValue ;
        return ans ;
    }
    else if(currNode -> op == '*')
    {
        double ans = leftValue * rightValue ;
        return ans ;
    }
    else if(currNode -> op == '-')
    {
        double ans = leftValue - rightValue ;
        return ans ;
    }
    else if(currNode -> op == '/')
    {
        double ans = leftValue / rightValue ;
        return ans ;
    }
}

// returns the infix expression with brackets added
string ExpTree::getInfix()
{
    if(root == NULL)
    {
        return "" ;
    }
    else
    {
        string finalString = getInfixRecurse(root) ;
        if(finalString[0] == '(' )
        {
            finalString = finalString.substr(1, finalString.length()-2 ) ;
        }

        return finalString ;
    }
}

// recursive function called by getInfix():
string ExpTree::getInfixRecurse(shared_ptr<node> currNode)
{
    if( !checkOperator(currNode -> op) )
    {
        string s(1, currNode -> op) ;
        return s ;
    }

    return  "(" + getInfixRecurse(currNode -> left) + currNode -> op + getInfixRecurse(currNode -> right) + ")"  ;
}

// check if it is operator
bool ExpTree::checkOperator(char s )
{
	if (s == '+' || s == '-' || s == '*' || s == '/' ||s == '^')
    {
        return true ;
    }
    else
    {
        return false;
    }
}

double ExpTree::getVal(char alphabet, vector<Variable> variables)
{
    return variables[alphabet - 'a'].value;
}

#endif