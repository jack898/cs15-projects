/*
 *  unit_tests.h
 *  Jack Burton
 *  9/30/2023
 *
 *  CS 15 Proj 1 MetroSim
 *
 *  Uses Matt Russell's unit_test framework to test MetroSim.
 *
 */

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Train.h"
#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"


/******************************************************************************/
/*  Passenger Class Tests                                                     */
/******************************************************************************/


// Ensure print() function works for Passenger initialized w/ default 
// constructor.
void print_default_passenger() {
    Passenger foo;
    std::stringstream ss;

    foo.print(ss);
    assert(ss.str() == "[-1, -1->-1]");
}

// Ensure print() function works for Passenger with other numbers (using
// other constructor).
void print_random_passenger() {
    Passenger foo(22, 4, 5);
    std::stringstream ss;
    
    foo.print(ss);
    assert(ss.str() == "[22, 4->5]");
}


/******************************************************************************/
/*  PassengerQueue Class Tests                                                */
/******************************************************************************/

// front() TESTS
// Ensure front() prints front Passenger for three-Passenger queue.
void print_front_normal_passengerlist() {
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    Passenger three(4, 5, 6);
    PassengerQueue list;

    list.enqueue(one);
    list.enqueue(two);
    list.enqueue(three);
    
    Passenger first = list.front();
    std::stringstream ss;
    first.print(ss);

    assert(ss.str() == "[1, 2->3]");
}

// enqueue() TESTS

// Ensure enqueue() adds five elements to a queue properly.
void enqueue_five_elements() {
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    Passenger three(4, 5, 6);
    Passenger four(6, 7, 8);
    Passenger five(8, 9, 10);
    Passenger first;
    PassengerQueue list;

    list.enqueue(one);

    // Check that element one is at the front of the queue
    first = list.front();
    std::stringstream ss;
    first.print(ss);
    assert(ss.str() == "[1, 2->3]");  

    list.enqueue(two);
    list.enqueue(three);
    list.enqueue(four);
    list.enqueue(five);

    // Check that element one is still at the front of the queue
    first = list.front();
    std::stringstream ss2;
    first.print(ss2);
    assert(ss.str() == "[1, 2->3]"); 
}

// dequeue() TESTS

// Ensure dequeue() works for a five element PassengerQueue
void dequeue_five_elements() {
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    Passenger three(4, 5, 6);
    Passenger four(6, 7, 8);
    Passenger five(8, 9, 10);
    Passenger first;
    PassengerQueue list;
    list.enqueue(one); 
    list.enqueue(two);
    list.enqueue(three);
    list.enqueue(four);
    list.enqueue(five);
    
    // Remove front three elements
    list.dequeue();
    list.dequeue();
    list.dequeue();

    // Check that front element is now four
    first = list.front();
    std::stringstream ss;
    first.print(ss);
    assert(ss.str() == "[6, 7->8]");    
}

// size() TESTS

// Ensure size() works for an empty queue
void size_empty_list() {
    PassengerQueue list;

    assert(list.size() == 0);
}

// Ensure size() works for a queue with elements added/deleted
void size_enqueue_dequeue_list() {
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    Passenger three(4, 5, 6);
    Passenger four(6, 7, 8);
    Passenger five(8, 9, 10);
    Passenger first;
    PassengerQueue list;

    // Add five elements to queue
    list.enqueue(one); 
    list.enqueue(two);
    list.enqueue(three);
    list.enqueue(four);
    list.enqueue(five);

    assert(list.size() == 5);
    
    // Remove front three elements
    list.dequeue();
    list.dequeue();
    list.dequeue();

    assert(list.size() == 2);
}

// print() TESTS

// Ensure print() prints nothing for an empty PassengerQueue
void print_empty_passengerlist() {
    PassengerQueue list;
    std::stringstream ss;
    list.print(ss);

    assert(ss.str() == "");
}

// Ensure print works properly for a three element queue
void print_three_element_list() {
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    Passenger three(4, 5, 6);
    PassengerQueue list;

    // Add three elements to queue
    list.enqueue(one); 
    list.enqueue(two);
    list.enqueue(three);

    std::stringstream ss;
    list.print(ss);
    assert(ss.str() == "[1, 2->3][2, 3->4][4, 5->6]");
}


/******************************************************************************/
/*  Train Class Tests                                                         */
/******************************************************************************/

// Constructor TESTS

// See if Train constructor properly builds a train from given
// testing stations.txt file
void train_constructor_normal_station_file() {
    std::ifstream instream;
    instream.open("stations.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();
    
    // Stations added to stationNames vector in same order as added to train,
    // so sufficient way to check if train vector was also built properly.

}

// addPQ() TESTS

// Tests if addPQ properly adds PassengerQueues to empty vector
void addPQ_empty_vector() {
    Train train; // initialize an empty Train
    assert(train.size() == 0);
    PassengerQueue test;
    train.addPQ(test);
    assert(train.size() == 1); // ensure train is no longer empty (PQ was added)
}

// Ensure addPQ works on a nonempty list
void addPQ_nonempty_list() {
    Train train; // initialize an empty Train
    assert(train.size() == 0);
    PassengerQueue test, test2;
    train.addPQ(test);
    train.addPQ(test2);
    assert(train.size() == 2);
}

// returnPQ() TESTS

// Ensure returnPQ() works on a vector with multiple PassengerQueues
void returnPQ_multiple_PQ_vector() {
    Train train; // initialize an empty Train
    PassengerQueue test, test2;
    Passenger one(1, 2, 3);
    Passenger two(2, 3, 4);
    // add Passengers to PQs
    test.enqueue(one); 
    test2.enqueue(two);

    train.addPQ(test);
    train.addPQ(test2);
    PassengerQueue& test3 = train.returnPQ(0);
    test3.dequeue();
    std::stringstream ss;
    test3.print(ss); // print PQ test3's contents to stringstream
    std::stringstream ss2;
    train.returnPQ(0).print(ss2);
    assert(ss.str() == "");
    assert(ss2.str() == "");
}

// returnTrainCars() TESTS

// Ensure returnCars prints the train properly when no Passengers are on board
void returnTrainCars_no_passengers() {
    Train train;
    assert(train.returnTrainCars() == "");
}

// Ensure returnTrainCars prints train properly with one passenger
void returnTrainCars_one_pass() {
    Train train;
    Passenger one(1, 2, 3);
    PassengerQueue list;
    list.enqueue(one);;
    train.addPQ(list);
    assert(train.returnTrainCars() == "[1, 2->3]");
}

// Ensure returnTrainCars prints train properly with multiple passengers
// NOTE: PQs will always be added in order from addPQ function, so no need to
// test for out-of-order train. Not added in same order as in real game
// here, just testing that they get concatenated properly.
void returnTrainCars_multiple_pass() {
    Passenger one(1, 2, 3);
    Passenger two(2, 2, 3);
    Passenger three(3, 5, 3);
    PassengerQueue station1;
    station1.enqueue(one); 
    station1.enqueue(two);
    station1.enqueue(three);

    
    Passenger four(4, 5, 6);
    Passenger five(5, 2, 6);
    Passenger six(6, 1, 6);
    PassengerQueue station2;
    station2.enqueue(four);
    station2.enqueue(five);
    station2.enqueue(six);

    Train train; // create train and add both PQs to it
    train.addPQ(station1);
    train.addPQ(station2);

    // Ensure it prints them in correct order
    assert(train.returnTrainCars() == 
    "[1, 2->3][2, 2->3][3, 5->3][4, 5->6][5, 2->6][6, 1->6]");

}


/******************************************************************************/
/*  MetroSim Class Tests                                                      */
/******************************************************************************/
// NOTE: Many functions here checked manually by looking at stdout from 
// updateUI() function; since this is >25 lines would be tedious to try to 
// represent as string to compare with assert. Primarily compared using diff 
// testing after visually confirming it appeared correct.

// initPQVectors() TESTS

// Ensures initPQVectors generates correct list of stations from given
// stations.txt file.
void initPQvectors_given_stations_file() {
    std::ifstream instream;
    instream.open("stations.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.updateUI();
}

// Ensures initPQVectors generates correct list of stations from a stations
// file with only two stations
// NOTE: Also checked manually by looking at stdout for same reasons as above.
void initPQvectors_short_stations_file() {
    std::ifstream instream;
    instream.open("stations2.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.updateUI();
}

// updateUI() TESTS

// Ensures updateUI couts the correct UI after train has moved stations.
// Further functions also test updateUI for more train/passenger movements.
void updateUI_train_moved() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.updateUI();
    game.metroMove(outstream); // move train to next station. Train should 
                               // appear at station 1.
    outstream.close();
}

// metroMove() TESTS

// Verify that metroMove shifts train back to first station if at last
// station
void metroMove_no_passengers_loop_around() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.updateUI();
    game.metroMove(outstream); // move train to next station
    game.metroMove(outstream); // move train to next station when at last,
                      // should now appear at station 0 again.
    outstream.close();
}

// Verify that metroMove correctly picks up Passenger at station 0 and drops
// them at station 1.
void metroMove_one_passenger_one_station() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.addPassenger(0, 1);
    game.updateUI(); // Passenger [1, 0->1] should appear at station [0]
    game.metroMove(outstream); // Passenger [1, 0->1] should appear on train
    outstream.close();
}

// Verify that metroMove correctly picks up Passenger at station 0 and drops
// them at station 0 when moved to station 1. Also ensures valgrind passes, i.e.
// passenger is properly deleted when dequeued.
void metroMove_onepass_same_station() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.addPassenger(0, 0); // Passenger [1, 0->0] should appear at station [0]
    game.metroMove(outstream); // Passengers [1, 0->0] should be on train
    game.metroMove(outstream); // Passenger [1, 0->0] should be gone
    outstream.close();
}

// Verify that metroMove correctly picks up two passengers at same station
// and drops them both off at same station
void metroMove_multiple_pass_same_depart_arrive() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.addPassenger(0, 1);
    game.addPassenger(0, 1); // Passengers [1, 0->1] and [2, 0->1] 
                             // should appear at station [0]
    game.metroMove(outstream); // Passengers [1, 0->1] and [2, 0->1] 
                               // should be on train
    outstream.close();

}

// Verify that metroMove correctly picks up two passengers at seperate stations
// and drops them off at the correct stations
void metroMove_multiple_pass_diff_depart_arrive() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    game.addPassenger(0, 1); // Passenger [1, 0->1] should appear at station 0
    game.addPassenger(1, 0); // Passenger [2, 1->0] should appear at station 1
    game.metroMove(outstream); // pass 1 should be gone, 
                               // pass 2 should be at station 1
    game.metroMove(outstream); // pass 2 should be gone
    outstream.close();

}

// addPassenger() TESTS

// Verify that addPassenger() adds multiple passengers to multiple diff stations
// (and multiple at the same station)
void addPassengers_multiple_same_station() {
    std::ifstream instream;
    std::ofstream outstream;
    instream.open("stations2.txt");
    outstream.open("outTest.txt");
    MetroSim game;
    game.initPQVectors(instream);
    instream.close();

    for (int i = 0; i < 40; i++) { // 40 Passengers should appear at station 0
        game.addPassenger(0, 1);
    }
}
