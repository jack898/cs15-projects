/*
 *  PassengerQueue.h
 *  Jack Burton
 *  9/30/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  PassengerQueues hold Passengers who are waiting to board or depart from
 *  trains. They essentially act as "train cars", with each one 
 *  corresponding to a particular station.
 *
 */


#ifndef __PASSENGER_QUEUE_H__
#define __PASSENGER_QUEUE_H__

#include <iostream>
#include <list>
#include "Passenger.h"

class PassengerQueue {
public:
    // Constructor/destructor implemented by default in std::list

    // PassengerQueue Interface Functions
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

private:
    std::list<Passenger> passengers;
};

#endif
