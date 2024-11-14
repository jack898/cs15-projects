/*
 *  RPNCalc.h
 *  Jack Burton
 *  10/12/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Implement a reverse polish notation calculator that can also 
 *  perform various functions with rstrings and file inputs.
 *
 */

#ifndef RPN_CALC_H
#define RPN_CALC_H

#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"

class RPNCalc {
public:
    void processCommand(std::istream &input);
    void run();


private:
    // Helper functions
    bool gotInt(std::string s, int *resultp);
    void notHandler();
    void printHandler();
    void swapHandler();

    void mathHandler(std::string input);
    void compareHandler(std::string input);
    int performOperation(std::string operation, int num1, int num2);
    bool performComparison(std::string comparison, int num1, int num2);

    void execHandler();
    void fileHandler();
    void readAndProcess(std::istream &input);
    void ifHandler();


    DatumStack stack;
    bool quitThrown; // track if quit is thrown
};

#endif
