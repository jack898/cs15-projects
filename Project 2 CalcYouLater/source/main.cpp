/*
 *  main.cpp
 *  Jack Burton
 *  10/18/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Main driver function to start CalcYouLater
 *
 */

#include <string>

#include "RPNCalc.h"

using namespace std;


/*
 * name:      main
 * purpose:   main driver function for CalcYouLater
 * arguments: none
 * returns:   int
 * effects:   RPNCalc class
 */
int main()
{
        RPNCalc calc; // initialize new RPNCalc instance
        calc.run();
        
        return 0;
}

