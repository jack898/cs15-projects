// Author: Jack Burton, Maurice Jang
// Date: Dec 10, 2023
//
// CS 15 Project 4: Gerp
// File name: main.cpp
//
// Purpose: main driver function for Gerp program

#include "query.h"

using namespace std;


// Name: main
// Purpose: main driver function to run query loop with a search directory
// Input: int with number of arguments, array of char pointers with arguments
// Output: int with exit status
// Effects: Query class instance
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }
    
    ofstream outstream(argv[2]);
    Query instance; 
    string directory = argv[1];
    instance.queryLoop(directory, outstream);

    cout << "Goodbye! Thank you and have a nice day." << endl;

    return 0;
}




