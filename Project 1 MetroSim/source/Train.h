/*
 *  Train.h
 *  Jack Burton
 *  9/30/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Train is a class built of std::vectors of PassengerQueues, each 
 *  PassengerQueue representing a "train car" and corresponding to a station 
 *  in the stations vector in the MetroSim class.
 *  
 */


#ifndef __TRAIN_H__
#define __TRAIN_H__

#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "PassengerQueue.h"

class Train {
public:
        // Train implementation functions
        int size();

        // PassengerQueue vector getter and setter
        void addPQ(PassengerQueue toAdd);
        PassengerQueue& returnPQ(int stationId);

        // currentStation() getter and setter
        int getCurrentStation();
        void moveStations(int totalStations);
        
        std::string returnTrainCars();

private:
        std::vector<PassengerQueue> train;
        int currentStation = 0; // start at station 0
};

#endif
