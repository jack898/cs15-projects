// Author: Jack Burton, Maurice Jang
// Date: Dec 10, 2023
//
// CS 15 Project 4: Gerp
// Name: query.cpp
//
// Purpose: implementation of query class functions.

#include "query.h"

using namespace std;


// Name: queryLoop
// Purpose: query a user repeatedly for commands
// Input: reference to a search directory string, reference to an output
// file stream.
// Output: nothing
// Effects: touches the hash indirectly
void Query::queryLoop(string &searchDir, ofstream &outstream) {
    Index indexedDir(searchDir);
    string command = ""; 

    cout << "Query? ";
    while (cin >> command) {

        if (command == "@q" or command == "@quit") 
            return;  
        else if (command == "@f") { 
            outstream.close(); 
            cin >> command;
            outstream.open(command);
        } else if (command == "@i" or command == "@insensitive") {
            cin >> command; 
            outstream << indexedDir.searchTableWrapper(command, false);
        } else 
            outstream << indexedDir.searchTableWrapper(command, true);

        cout << "Query? ";
    }  
}
