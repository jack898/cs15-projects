/*
 *  DatumStack.h
 *  Jack Burton
 *  10/12/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Store a stack of Datum objects which can be popped/pushed, along with 
 *  functions to check the size and state of the stack.
 *
 */

#ifndef DATUM_STACK_H
#define DATUM_STACK_H

#include <string>
#include <list>
#include "Datum.h"

class DatumStack {
public:
    // Constructor
    DatumStack();
    DatumStack(Datum arr[], int size);
    // big three implemented by default by std::list

    // Implementation Functions
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum val);

private:
    std::list<Datum> stack;
};

#endif
