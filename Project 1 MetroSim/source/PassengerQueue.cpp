/*
 *  PassengerQueue.cpp
 *  Jack Burton
 *  9/30/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Implements the PassengerQueue class functions.
 *
 */

#include <iostream>
#include <string>
#include <list>
#include "PassengerQueue.h"
#include "Passenger.h"


/*
 * name:      front
 * purpose:   returns front Passenger in respective PassengerQueue
 * arguments: none
 * returns:   Passenger element
 * effects:   none
 */
Passenger PassengerQueue::front() {
    return passengers.front();
}

/*
 * name:      enqueue
 * purpose:   inserts new Passenger at end of the queue
 * arguments: reference to a Passenger
 * returns:   none
 * effects:   passengers std::list
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    passengers.push_back(passenger);
}

/*
 * name:      dequeue
 * purpose:   removes Passenger at front of the queue
 * arguments: none
 * returns:   none
 * effects:   passengers std::list
 */
void PassengerQueue::dequeue() {
    passengers.pop_front();
}

/*
 * name:      size
 * purpose:   returns the number of elements in a queue
 * arguments: none
 * returns:   int with num of elements from a queue
 * effects:   none
 */
int PassengerQueue::size() {
    return passengers.size();
}

/*
 * name:      print
 * purpose:   prints each Passenger in a PassengerQueue to given ostream
 * arguments: reference to output stream
 * returns:   none
 * effects:   none
 */
void PassengerQueue::print(std::ostream &output) {
    std::list<Passenger>::iterator it;
    for (it = passengers.begin(); it != passengers.end(); it++) {
        it->print(output);
    }
}







