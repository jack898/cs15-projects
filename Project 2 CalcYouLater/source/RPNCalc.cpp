/*
 *  RPNCalc.cpp
 *  Jack Burton
 *  10/12/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Implements the RPNCalc class functions.
 *
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"

using namespace std;


/*
 * name: processCommand     
 * purpose: handle user commands appropriately
 * arguments: reference to an input stream
 * returns: none
 * effects: none
 */
void RPNCalc::processCommand(istream &command) {
    int num;
    string input, rString;
    command >> input;
    if (input == "clear") { // No try because never throws errors
        stack.clear();
    }
    else if (input == "not") {
        try {
            notHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "print") {
        try {
            printHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "drop") {
        try {
            stack.pop();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "dup") {
         try {
            stack.push(stack.top());
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }       
    }
    else if (input == "swap") {
        try {
            swapHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "+" or input == "-" or input == "*" or input == "/" or 
    input == "mod") { // math operations
        try {
            mathHandler(input);
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "<" or input == ">" or input == "<=" or input == ">=" or 
    input == "==") { // comparison operations
        try {
            compareHandler(input);
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "{") { // storing rStrings in stack
        rString = parseRString(command);
        stack.push(Datum(rString));
    }
    else if (input == "exec") {
        try {
            execHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "file") {
        try {
            fileHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (input == "if") {
        try {
            ifHandler();
        }
        catch (const runtime_error &e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
    else if (gotInt(input, &num)) { // storing ints in stack
        stack.push(Datum(num));
    }
    else if (input == "#t") { // storing bools in stack
        stack.push(Datum(true));
    }
    else if (input == "#f") {
        stack.push(Datum(false));
    }
    else if (input == "quit" or input == "") { // catching quit and eof cases
        quitThrown = true;
        return;
    }
    else {
        cerr << input << ": unimplemented\n";
    }
}

/*
 * name: run     
 * purpose: recursively prompt user for commands and send to processing function
 * arguments: none
 * returns: none
 * effects: none
 */
void RPNCalc::run() {
    quitThrown = false;
    processCommand(cin);
    // while still input and user has not typed quit
    while (not cin.eof() and not quitThrown) {
        processCommand(cin);
    }

    cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name: got_int     
 * purpose: determines if string is an integer, and places the int in resultp
 * if so.
 * arguments: string, pointer to an int
 * returns: bool indicating if string is integer
 * effects: integer put in resultp if string is integer
 */
bool RPNCalc::gotInt(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name: notHandler    
 * purpose: pops top element off stack, and if bool, pushes opposite value
 * arguments: none
 * returns: none
 * effects: stack
 */
void RPNCalc::notHandler() {
    Datum top = stack.top();
    stack.pop();
    bool datumBool = top.getBool(); // to ensure bool, or throw error if not

    stack.push(Datum(not datumBool));
}

/*
 * name: printHandler   
 * purpose: prints top element from stack to cout
 * arguments: none 
 * returns: none
 * effects: none
 */
void RPNCalc::printHandler() {
    Datum top = stack.top();
    if (top.isBool()) { 
        bool value = top.getBool();
        if (value) {
            cout << "#t" << endl;
        } 
        else {
            cout << "#f" << endl;
        }
    }
    else if (top.isInt()) {
        cout << top.getInt() << endl;
    }
    else if (top.isRString()) {
        cout << top.getRString() << endl;
    }
}

/*
 * name: swapHandler    
 * purpose: swaps top two elements on stack
 * arguments: none
 * returns: none
 * effects: stack
 */
void RPNCalc::swapHandler() {
    Datum temp1 = stack.top();
    stack.pop();
    Datum temp2 = stack.top();
    stack.pop();

    stack.push(temp1);
    stack.push(temp2);
}

/*
 * name: mathHandler    
 * purpose: performs arithmetic operation on top two elements of stack
 * arguments: string with math operation
 * returns: none
 * effects: stack
 */
void RPNCalc::mathHandler(string input) {
    Datum temp1 = stack.top();
    stack.pop();
    Datum temp2 = stack.top();
    stack.pop();

    if (temp1.isInt() and temp2.isInt()) {
        int num1 = temp1.getInt();
        int num2 = temp2.getInt();
        // Catch divide by zero edge case for mod and division
        if (num1 == 0 and (input == "/" or input == "mod")) {
            throw runtime_error("division by 0.");
        }
        int result = performOperation(input, num1, num2);
        stack.push(Datum(result));
    }
    else { // Catch if either Datum is not an int
        throw runtime_error("datum_not_int");
    }
}

/*
 * name: performOperation    
 * purpose: calculates and returns arithmetic operation on num1 and num2
 * arguments: string with math operation, two integers
 * returns: int with appropriate operation applied to num1 and num2
 * effects: none
 */
int RPNCalc::performOperation(string operation, int num1, int num2) {
    if (operation == "+") {
        return num2 + num1;
    }
    else if (operation == "-") {
        return num2 - num1;
    }
    else if (operation == "*") {
        return num2 * num1;
    }
    else if (operation == "/") {
            return num2 / num1;
        }  
    return num2 % num1; // mod is only other math operation
}

/*
 * name: compareHandler    
 * purpose: performs comparison operation on top two elements of stack
 * arguments: string with comparison operation
 * returns: none
 * effects: stack
 */
void RPNCalc::compareHandler(string input) {
    Datum temp1 = stack.top();
    stack.pop();
    Datum temp2 = stack.top();
    stack.pop();

    if (temp1.isInt() and temp2.isInt()) {
        int num1 = temp1.getInt();
        int num2 = temp2.getInt();
        bool result = performComparison(input, num1, num2);
        stack.push(Datum(result));
    }
    else { // Catch if either Datum is not an int
        throw runtime_error("datum_not_int");
    }
}


/*
 * name: performComparison    
 * purpose: calculates and returns comparison operation on num1 and num2
 * arguments: string with comparison operation, two integers
 * returns: bool with result of comparison between num1 and num2
 * effects: none
 */
bool RPNCalc::performComparison(string operation, int num1, int num2) {
    if (operation == "<") {
        return num2 < num1;
    }
    else if (operation == ">") {
        return num2 > num1;
    }
    else if (operation == "<=") {
        return num2 <= num1;
    }
    else if (operation == ">=") {
            return num2 >= num1;
        }  
    return num2 == num1; // equality is only remaining comparison operation
}

/*
 * name: execHandler    
 * purpose: executes rString on top of stack
 * arguments: none
 * returns: none
 * effects: potentially stack
 */
void RPNCalc::execHandler() {
    Datum top = stack.top();
    stack.pop();
    if (top.isRString()) {
        std::istringstream iss (top.getRString());
        string word;
        iss >> word; // get rid of first opening bracket
        readAndProcess(iss);
    }
    else {
        throw runtime_error("cannot execute non rstring");
    }
}

/*
 * name: fileHandler    
 * purpose: handle a a .cyl file, executing its commands
 * arguments: none
 * returns: none
 * effects: potentially stack
 */
void RPNCalc::fileHandler() {
    Datum top = stack.top();
    stack.pop();
    if (top.isRString()) {
        std::istringstream iss (top.getRString());
        ifstream instream;
        string junk, fileName, word;
        iss >> junk >> fileName;
        instream.open(fileName);
        if (not instream.is_open()) {
            cerr << "Unable to read " << fileName << "\n";
            return;
        }
        readAndProcess(instream);
        instream.close();
    }
    else {
        throw runtime_error("file operand not rstring");
    }
}

/*
 * name: readAndProcess    
 * purpose: reads and processes a series of commands, including handling
 * command series from rStrings
 * arguments: reference to an input stream
 * returns: none
 * effects: potentially stack
 */
void RPNCalc::readAndProcess(istream &input) {
    string word; 
    while (input >> word and word != "}") {
        std::stringstream wordStream;
        if (word == "{") { // handle if rString is nested
            wordStream << parseRString(input);
        }
        else { // otherwise push command to stream
            wordStream << word;
        }
        processCommand(wordStream); // execute command
    }
}

/*
 * name: ifHandler    
 * purpose: handles the if command, executing the appropriate case based on 
 * test condition
 * arguments: none
 * returns: none
 * effects: potentially stack
 */
void RPNCalc::ifHandler() {
    Datum top = stack.top(); // pop and store top 3 elements from stack
    stack.pop();
    Datum middle = stack.top();
    stack.pop();
    Datum bottom = stack.top();
    stack.pop();
    // Handle potential errors with if input
    if (not top.isRString() or not middle.isRString()) {
        throw runtime_error("expected rstring in if branch");
    }
    else if (not bottom.isBool()) {
        throw runtime_error("expected boolean in if test");
    }

    // If past errors, execute appropriate case
    bool testCondition = bottom.getBool();
    std::stringstream rString, exec;
    if (testCondition) {
        rString << middle.getRString();
    }
    else {
        rString << top.getRString();
    }
    exec << "exec";
    processCommand(rString);
    processCommand(exec);
}
