/*
 *  parser.cpp
 *  Jack Burton
 *  10/13/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Implements the parser class function.
 *
 */

#include <string>
#include <iostream>
#include <sstream>
using namespace std;


/*
 * name: parseRString     
 * purpose: reads an input stream into an rstring (i.e. std::string)
 * arguments: reference to an input stream
 * returns: string
 * effects: none
 */
string parseRString(istream &input) {
    string output = "{ ";
    string temp;
    while(input >> temp) {
        if (temp == "{") {
            output += parseRString(input) + " ";
        }
        else if (temp == "}") {
            output += "}";
            return output;
        }
        else {
            output += temp + " ";
        }
    }

    return output;
}

