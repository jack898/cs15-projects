/*
 *  Train.cpp
 *  Jack Burton
 *  10/3/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Implements the Train class functions.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"
#include "Train.h"

using namespace std;

/*
 * name:      addPQ
 * purpose:   adds PassengerQueue to the back of train
 * arguments: a PassengerQueue to add to the back
 * returns:   none
 * effects:   train std::vector
 */
void Train::addPQ(PassengerQueue toAdd) {
        train.push_back(toAdd);
}

/*
 * name:      returnPQ
 * purpose:   returns specified PassengerQueue (station)
 * arguments: int with a station id
 * returns:   reference to PassengerQueue instance
 * effects:   none
 */
PassengerQueue& Train::returnPQ(int stationId) {
        return train.at(stationId);
}

/*
 * name:      size
 * purpose:   returns size of train (i.e. number of PQs in it)
 * arguments: none
 * returns:   int
 * effects:   none
 */
int Train::size() {
        return train.size();
}


/*
 * name:      returnTrainCars
 * purpose:   returns current state of the train (all of the PassengerQueues
 * in proper order)
 * arguments: none
 * returns:   string
 * effects:   none
 */
string Train::returnTrainCars() {
        PassengerQueue temp;
        stringstream trainPassengers;
        // PRINT THESE NOT BY PQ ORDER BUT BY PASSENGER BOARDING ORDER
        for (int i = 0; i < int(train.size()); i++) {
                temp = train.at(i);
                temp.print(trainPassengers);
        }
        return trainPassengers.str();
}

/*
 * name:      getCurrentStation
 * purpose:   returns the station id of current station train is at
 * arguments: none
 * returns:   int with station id
 * effects:   none
 */
int Train::getCurrentStation() {
        return currentStation;
}

/*
 * name:      moveStations
 * purpose:   iterate train currentStation to next station
 * arguments: int representing total number of stations
 * returns:   none
 * effects:   currentStation value for a train
 */
void Train::moveStations(int totalStations) {
        if (currentStation == totalStations - 1) { // loop to first station if
                currentStation = 0;            // reached the last one
                return;
        }
        currentStation++;
}

