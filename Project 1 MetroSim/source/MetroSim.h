/*
 *  MetroSim.h
 *  Jack Burton
 *  10/3/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  MetroSim is a class which contains a vector of PassengerQueues, representing
 *  the stations from a stationsFile, and contains functions which operate the
 *  MetroSim game itself, such as updating the UI and running user commands.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "PassengerQueue.h"
#include "Train.h"

class MetroSim
{
public:
    void initPQVectors(std::ifstream &stationsFile);
    
    // MetroSim Implementation Functions
    void promptCommands(std::ofstream &outstream);
    void runCommand(std::stringstream &cmd, std::ofstream &outstream);
    void metroMove(std::ofstream &outstream);
    void addPassenger(int arrival, int depart);
    
    void updateUI();


private:
    Train train; // Train object for MetroSim instance
    std::vector<PassengerQueue> stations;
    std::vector<std::string> stationNames;
    int passengerID = 0;

    // Helper functions
    void printStations();
    void passBoardingHelper(PassengerQueue& stationToCheck);
    void passDepartHelper(int currentStation, std::ofstream& outstream);
};

#endif
