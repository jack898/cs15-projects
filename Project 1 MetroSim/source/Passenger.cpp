/*
 *  Passenger.cpp
 *  Jack Burton
 *  9/30/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Implement the Passenger class functions.
 *
 */


#include <iostream>
#include <string>
#include <sstream>
#include "Passenger.h"

/*
 * name:      print
 * purpose:   print passenger information to ostream 
 * arguments: reference to output stream to print to
 * returns:   none
 * effects:   none
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
