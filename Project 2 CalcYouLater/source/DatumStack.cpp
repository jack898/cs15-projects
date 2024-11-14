/*
 *  DatumStack.cpp
 *  Jack Burton
 *  10/12/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Implements the DatumStack class functions.
 *
 */

#include <string>
#include <iostream>
#include "Datum.h"
#include "DatumStack.h"

using namespace std;


/*
 * name:      Default Constructor
 * purpose:   initialize an empty DatumStack
 * arguments: none
 * returns:   none
 * effects:   stack list
 */
DatumStack::DatumStack() {
}

/*
 * name:      Overloaded Constructor
 * purpose:   initialize a stack with Datums from array
 * arguments: array of Datums, int indicating size
 * returns:   none
 * effects:   stack list
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        stack.push_front(arr[i]);
    }
}

/*
 * name:      isEmpty
 * purpose:   returns bool indicating if stack is empty
 * arguments: none
 * returns:   bool
 * effects:   none
 */
bool DatumStack::isEmpty() {
    return stack.empty();
}

/*
 * name:      clear
 * purpose:   makes current stack into an empty stack
 * arguments: none
 * returns:   none
 * effects:   stack
 */
void DatumStack::clear() {
    stack.clear();
}

/*
 * name:      size
 * purpose:   returns number of Datum elements on stack
 * arguments: none
 * returns:   int
 * effects:   none
 */
int DatumStack::size() {
    return stack.size();
}

/*
 * name:      top
 * purpose:   returns top Datum element from stack
 * arguments: none
 * returns:   Datum from stack
 * effects:   none
 */
Datum DatumStack::top() {
    if (stack.empty()) {
        throw std::runtime_error("empty_stack");
    }  
    return stack.front();
}


/*
 * name:      pop
 * purpose:   remove top element from stack
 * arguments: none
 * returns:   none
 * effects:   stack
 */
void DatumStack::pop() {
    if (stack.empty()) {
        throw std::runtime_error("empty_stack");
    }
    stack.pop_front();
}


/*
 * name:      push
 * purpose:   puts Datum element on top of stack
 * arguments: Datum element
 * returns:   none
 * effects:   stack
 */
void DatumStack::push(Datum val) {
    stack.push_front(val);
}

