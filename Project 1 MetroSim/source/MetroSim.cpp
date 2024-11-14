/*
 *  MetroSim.cpp
 *  Jack Burton
 *  10/3/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Implements the MetroSim class functions
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"
#include "Train.h"

using namespace std;

/*
 * name:      initPQVectors
 * purpose:   initializes the Station std::vector (in MetroSim class) and calls
 * function in Train class to add cars to train std::vector using the input
 * stationFile.
 * arguments: Reference to an ifstream
 * returns:   PassengerQueue instance
 * effects:   station vector, stationNames vector, and train vector 
 * via Train functions
 */
void MetroSim::initPQVectors(std::ifstream &stationsFile) {
        string currentLine;
        while (getline(stationsFile, currentLine)) {
                PassengerQueue temp;
                stations.push_back(temp); // add to back of stations arr
                stationNames.push_back(currentLine); // store station name str
                train.addPQ(temp); // add to back of train arr
        } 
}

/*
 * name:      updateUI
 * purpose:   prints the UI after each command
 * arguments: none
 * returns:   none
 * effects:   none
 */
void MetroSim::updateUI() {
    cout << "Passengers on the train: " << "{" << train.returnTrainCars() 
    << "}" << endl;

    printStations(); // prints the station list and 'Command?' prompt
}

/*
 * name:      printStations
 * purpose:   private helper for updateUI that iterates through station list
 * and prints them, also printing TRAIN: at currentStation
 * arguments: none
 * returns:   none
 * effects:   none
 */
void MetroSim::printStations() {
    stringstream stationLines;
    for (int i = 0; i < int(stations.size()); i++) {
        if (train.getCurrentStation() == i) { // if train is at current station
            stationLines << "TRAIN: ";
        } 
        else {
            stationLines << "       ";
        }
        stationLines << "[" << i << "] " << stationNames.at(i) << " {"; 
        stations.at(i).print(stationLines); // print passengers at station i
        stationLines << "}" << endl;
   
    }
    // send fully concatenated sstream object to cout
    stationLines << "Command? ";
    cout << stationLines.str(); 
}

/*
 * name:      metroMove
 * purpose:   iterates train to next station, removing passengers if they depart
 * there and adding passengers if they board there.
 * arguments: reference to outstream
 * returns:   none
 * effects:   potentially stations and/or train vectors if passengers are
 * boarding/departing
 */
void MetroSim::metroMove(ofstream &outstream) {
    int numStations = int(stations.size());
    int currentStation = train.getCurrentStation();
    PassengerQueue& stationToCheck = stations.at(currentStation);

    // Board any passengers from current station
    passBoardingHelper(stationToCheck);

    train.moveStations(numStations); // move train to next station
    currentStation = train.getCurrentStation();

    // Dequeue any passengers exiting train at new station
    passDepartHelper(currentStation, outstream);

    updateUI(); // update the UI
}

/* 
 * name:      passDepartHelper
 * purpose:   removes passenger from train
 * arguments: int for current station index, reference to outstream
 * returns:   none
 * effects:   train vector
 */
void MetroSim::passDepartHelper(int currentStation, ofstream &outstream) {
    while (train.returnPQ(currentStation).size() != 0) {
        outstream << "Passenger " << train.returnPQ(currentStation).front().id
        << " left train at station " << stationNames.at(currentStation) << "\n";
        train.returnPQ(currentStation).dequeue();
    }
}

/* 
 * name:      passBoardingHelper
 * purpose:   boards passenger onto trainCar from stationToCheck
 * arguments: reference to station to check for passengers
 * returns:   none
 * effects:   stations vector, train vector
 */
void MetroSim::passBoardingHelper(PassengerQueue& stationToCheck) {
    Passenger temp;
    while (stationToCheck.size() != 0) { 
        temp = stationToCheck.front();
        train.returnPQ(temp.to).enqueue(temp);
        stationToCheck.dequeue();
    }
} 

/*
 * name:      addPassenger
 * purpose:   adds a Passenger to arrival station PassengerQueue
 * arguments: int for arrival station and int for departing station
 * returns:   none
 * effects:   stations vector
 */
void MetroSim::addPassenger(int arrival, int depart) {
    passengerID++;
    PassengerQueue& station = stations.at(arrival); 
    // Create a new Passenger and enqueue them at correct station
    station.enqueue(Passenger(passengerID, arrival, depart));
    updateUI(); // update game UI
}

/*
 * name:      promptCommands
 * purpose:   recursively prompt user for commands/print thanks metrofinish 
 * message
 * arguments: reference to outstream
 * returns:   none
 * effects:   stations vector
 */
void MetroSim::promptCommands(ofstream &outstream) {
    string input, cmdString1, cmdString2, cmdString3;
    getline(cin, input);
    stringstream currCmd(input);
    if (currCmd.str() == "m f") { // base case
        cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
        return;
    }
    // recursive case: run command and prompt for another
    runCommand(currCmd, outstream); 
    promptCommands(outstream);
}

/*
 * name:      runCommand
 * purpose:   parse and execute user command
 * arguments: reference to a stringstream, reference to a file outstream
 * returns:   none
 * effects:   touches train and stations vectors via other
 *            command functions
 */
void MetroSim::runCommand(stringstream &cmd, ofstream &outstream) {
    string junkLine, arrive, depart;
    if (cmd.str() == "m m") { 
            metroMove(outstream);
    } 
    else { // assuming valid commands, this must be "p" command
            cmd >> junkLine >> arrive >> depart;
            addPassenger(stoi(arrive), stoi(depart));
    }    
}