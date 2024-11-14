/*
 *  main.cpp
 *  Jack Burton
 *  10/3/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Handles simple driver functions, such as reading in files.
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"
#include "Train.h"
#include "Passenger.h"
#include "PassengerQueue.h"

using namespace std;


// Simple driver functions placed into main.cpp such as file opener, argc
// checker, file command parser
template <typename streamtype>
void openFile(streamtype &stream, string fileName);
void argCheck(int numArgs);
void fileCommands(MetroSim &game, ifstream &instream, ofstream &outstream);


/*
 * name:      main
 * purpose:   main driver function for MetroSim
 * arguments: int with number of args, array of those args
 * returns:   int indicating whether program executed successfully or not
 * effects:   all classes (MetroSim, Passenger, PassengerQueue, Train) when 
 * executed with proper input. If improper input, affects nothing and exits.
 */
int main(int argc, char *argv[])
{
        argCheck(argc); // Ensure user gave proper number of args
        MetroSim game; // initialize new game instance

        ifstream instream;
        ofstream outstream;
        openFile(instream, argv[1]);
        game.initPQVectors(instream); // initialize game variables
        openFile(outstream, argv[2]);
        instream.close();

        if (argc == 4) {
                openFile(instream, argv[3]);
                game.updateUI();
                fileCommands(game, instream, outstream);
        } else {
                game.updateUI();
                game.promptCommands(outstream);
        }
        instream.close();
        outstream.close();
}

/*
 * name:      fileCommands
 * purpose:   read in commands from a file
 * arguments: reference to MetroSim game instance, reference to a file instream,
 * reference to a file outstream
 * returns:   none
 * effects:   all classes (MetroSim, Passenger, PassengerQueue, Train) when 
 * executed with proper input. If improper input, affects nothing and exits.
 */
void fileCommands(MetroSim &game, ifstream &instream, ofstream &outstream) {
        string currentLine;
        while (getline(instream, currentLine)) {
                stringstream command;
                command << currentLine;
                if (command.str() == "m f") {
                        cout << "Thanks for playing MetroSim. Have a nice day!"
                        << endl;
                        return;
                }
                game.runCommand(command, outstream);
        }
}

/*
 * name:      argCheck
 * purpose:   Throw cerr and exit if user gave improper number of args
 * arguments: int with number of arguments
 * returns:   none
 * effects:   none
 */
void argCheck(int numArgs) {
        if (numArgs > 4 or numArgs < 3) {
                cerr << 
                "Usage: ./MetroSim stationsFile outputFile [commandsFile]" <<
                endl;
                exit(EXIT_FAILURE);
        }
}


/*
 * name:      openFile
 * purpose:   generic file opening function
 * arguments: any streamtype reference, a string with a file name
 * returns:   none
 * effects:   Train class when given proper input, otherwise affects nothing
 * and exits.
 */
template <typename streamtype>
void openFile(streamtype &stream, string fileName) {
        stream.open(fileName);
        if (not stream.is_open()) {
                cerr << "Error: could not open file " << fileName << endl;
                exit(EXIT_FAILURE);
        }
}