/*
 *  main.cpp
 *  Jack Burton
 *  11/11/2023
 *
 *  CS 15 Proj 3 Zap
 *
 *  Main driver function to process command line args and call
 *  encoder/decoder functions.
 *
 */

#include <iostream>
#include <string>
#include "HuffmanCoder.h"

using namespace std;

// Helper to ensure valid arguments provided
void argChecker(int argc, char *argv[]);

/*
 * name:      main
 * purpose:   main driver function for Zap
 * arguments: int with number of args, array of those args
 * returns:   int indicating whether program executed successfully or not
 * effects:   HuffmanCoder class
 */
int main(int argc, char *argv[]) {
    HuffmanCoder instance;
    // Ensure valid arguments or throw EXIT_FAILURE
    argChecker(argc, argv);
    string zapOrUnzap = argv[1];

    if (zapOrUnzap == "zap") {
        instance.encoder(argv[2], argv[3]);
    }
    else {
        instance.decoder(argv[2], argv[3]);
    }
}

/*
 * name:      argChecker
 * purpose:   ensures valid arguments provided or exit if not
 * arguments: int with number of args, array of those args
 * returns:   none
 * effects:   none
 */
void argChecker(int argc, char *argv[]) {
    bool invalidArgs = false;
    if (argc != 4) { // check number of args
        invalidArgs = true;
    } else { // check that second arg is zap/unzap
        string zapArg = argv[1];
        if (zapArg != "zap" and zapArg != "unzap") {
            invalidArgs = true;
        }
    }

    if (invalidArgs) { // throw error/exit if invalid
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE);
    }
}