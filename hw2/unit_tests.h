/*
 *  unit_tests.h
 *  Jack Burton
 *  9/20/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  Uses Matt Russell's unit_test framework to test the CharLinkedList class.
 *
 */

#include "CharLinkedList.h"
#include <cassert>

// Does nothing! Just ensures class definition is synctatically correct.
void dummy_test() {
}

// **All constructor tests implicitly test the destructor too; if the
// destructor is not working, valgrind will not pass for these.

// DEFAULT CONSTRUCTOR/DESTRUCTOR TESTS

// Creates an empty CharLinkedList, ensuring default constructor
// runs without error.
void default_constructor_normal() {
    CharLinkedList h;
}

// ONE CHAR CONSTRUCTOR/DESTRUCTOR TESTS

// Creates a one char CharLinkedList, ensuring the one char constructor
// works properly
void onechar_constructor_normal() {
    CharLinkedList list('a');
    assert(list.toString() == "[CharLinkedList of size 1 <<a>>]");
    assert(list.size() == 1);
}

// CHAR LINKED LIST CONSTRUCTOR/DESTRUCTOR TESTS

// Creates a multi char CharLinkedList
void multichar_constructor_normal() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharLinkedList list(arr, 4);

    assert(list.toString() == "[CharLinkedList of size 4 <<abcd>>]");
}

// size() TESTS


// Ensures size holds the right value while increasing list size
void size_changing_list() {
    CharLinkedList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
        assert(test_list.size() == i + 1);
    }
}

// isEmpty() TESTS

// Ensure isEmpty() updates properly when a list is cleared
void isEmpty_shrunk_list() {
    char items[] = {'a','b','c','d','e','f','g','h','i','j'};
    CharLinkedList test(items, 10);

    assert(not test.isEmpty());

    test.clear();

    assert(test.isEmpty());
}

// insertAt() TESTS

// Tests correct insertion into an empty list.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharLinkedList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}


// Tests incorrect insertion into an empty list.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ba>>]");
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ab>>]");
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// list expansion works correctly.
void insertAt_many_elements() {
    
    CharLinkedList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() == 
    "[CharLinkedList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharLinkedList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharLinkedList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

// pushAtFront() TESTS

// Ensure pushAtFront works on an empty list
void pushatfront_empty_list() {
    CharLinkedList list;

    list.pushAtFront('a');
    assert(list.toString() == "[CharLinkedList of size 1 <<a>>]");
}

// Ensure pushAtFront works on a one node list
void pushatfront_onenode_list() {
    CharLinkedList list('a');

    list.pushAtFront('b');

    assert(list.toString() == "[CharLinkedList of size 2 <<ba>>]");
}


// Ensure pushAtFront works on multi char list
void pushatfront_multichar_list() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharLinkedList list(arr, 4);

    list.pushAtFront('z');

    assert(list.toString() == "[CharLinkedList of size 5 <<zabcd>>]");
}

// Ensure pushAtFront works when repeatedly called on multi char list
void pushatfront_loop_multichar_list() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharLinkedList list(arr, 4);
    for (int i = 0; i < 10; i++) {
        list.pushAtFront('z');
    }

    assert(list.toString() == 
    "[CharLinkedList of size 14 <<zzzzzzzzzzabcd>>]");
}

// pushAtBack() TESTS

// Ensure pushAtBack works on an empty list
void pushatback_empty_list() {
    CharLinkedList list;

    list.pushAtBack('a');
    assert(list.toString() == "[CharLinkedList of size 1 <<a>>]");
}

// Ensure pushAtBack works on a one node list
void pushatback_onenode_list() {
    CharLinkedList list('a');

    list.pushAtBack('b');

    assert(list.toString() == "[CharLinkedList of size 2 <<ab>>]");
}


// Ensure pushAtBack works on multi char list
void pushatback_multichar_list() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharLinkedList list(arr, 4);

    list.pushAtBack('z');

    assert(list.toString() == "[CharLinkedList of size 5 <<abcdz>>]");
}

// Ensure pushatback works when repeatedly called on multi char list
void pushatback_loop_multichar_list() {
    char arr[] = {'a', 'b', 'c', 'd'};
    CharLinkedList list(arr, 4);
    for (int i = 0; i < 10; i++) {
        list.pushAtBack('z');
    }

    assert(list.toString() == 
    "[CharLinkedList of size 14 <<abcdzzzzzzzzzz>>]");
}

// insertInOrder() TESTS

// See if insertInOrder works on an empty list
void insert_in_order_empty_list() {
    CharLinkedList list;

    list.insertInOrder('z');

    assert(list.toString() == "[CharLinkedList of size 1 <<z>>]");
}

// See if insertInOrder works on a one char list properly
void insert_in_order_onechar_list() {
    CharLinkedList list('b');
    list.insertInOrder('a');

    assert(list.toString() == "[CharLinkedList of size 2 <<ab>>]");
}

// See if insertInOrder works properly on a multi char list when inserting
// into last position (also tests with a capital letter to ensure that works)
void insert_in_order_back_of_multichar_list() {
    char items[] = {'a','b','c','d','e','f'};
    CharLinkedList list(items, 6);
    list.insertInOrder('Z');

    assert(list.toString() == "[CharLinkedList of size 7 <<Zabcdef>>]");
}

// See if insertInOrder works properly on multichar list when inserting in
// the middle of it
void insert_in_order_middle_multichar_list() {
    char items[] = {'a','b','c','e','f','g'};
    CharLinkedList list(items, 6);
    list.insertInOrder('d');

    assert(list.toString() == "[CharLinkedList of size 7 <<abcdefg>>]");
}

// toString() TESTS

// See if toString prints properly for an empty linked list
void to_string_empty() {
    CharLinkedList list1;

    std::string toStrMsg = list1.toString();

    assert(toStrMsg == "[CharLinkedList of size 0 <<>>]");
}

// See if toString prints properly for 1-char linked list
void to_string_1char() {
    CharLinkedList list2('a');

    std::string toStrMsg = list2.toString();

    assert(toStrMsg == "[CharLinkedList of size 1 <<a>>]");
}

// See if toString prints properly for multi-char linked list
void to_string_multi_char() {
    char items[] = {'A','l','i','c','e'};
    CharLinkedList list(items, 5);

    std::string toStrMsg = list.toString();

    assert(toStrMsg == "[CharLinkedList of size 5 <<Alice>>]");
}

// toReverseString() TESTS

// See if toReverseString prints properly for an empty linked list
void to_rev_string_empty() {
    CharLinkedList list1;

    std::string toStrMsg = list1.toReverseString();

    assert(toStrMsg == "[CharLinkedList of size 0 <<>>]");
}

// See if toReverseString prints properly for 1-char linked list
void to_rev_string_1char() {
    CharLinkedList list2('a');

    std::string toStrMsg = list2.toReverseString();

    assert(toStrMsg == "[CharLinkedList of size 1 <<a>>]");
}

// See if toReverseString prints properly for multi-char linked list
void to_rev_string_multi_char() {
    char items[] = {'A','l','i','c','e'};
    CharLinkedList list(items, 5);

    std::string toStrMsg = list.toReverseString();
    assert(toStrMsg == "[CharLinkedList of size 5 <<ecilA>>]");
}

// popFromBack() TESTS

// See if popFromBack() throws std::range_error and appropriate message
// when using on empty list
void pop_back_empty_list() {
    CharLinkedList list;
    bool runtime_error_thrown = false;

    std::string error_msg = "";

    try {
        list.popFromBack();
    }
    catch (std::runtime_error &e) {
        runtime_error_thrown = true;
        error_msg = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_msg == "cannot pop from empty LinkedList");    
}

// See if popFromBack() correctly removes last element of multichar list.
void pop_back_multichar_list() {
    char items[] = {'a','b','c','d','e','f'};
    CharLinkedList list(items, 6);

    list.popFromBack();

    assert(list.toString() == "[CharLinkedList of size 5 <<abcde>>]");
}

// See if popFromBack() correctly removes the element of a one-char list
void pop_back_onechar_list() {
    CharLinkedList list('a');

    list.popFromBack();

    assert(list.isEmpty());
}

// popFromFront() TESTS

// See if popFromFront() throws std::runtime_error and appropriate message
// when using on empty list
void pop_front_empty_list() {
    CharLinkedList list;
    bool runtime_error_thrown = false;

    std::string error_msg = "";

    try {
        list.popFromFront();
    }
    catch (std::runtime_error &e) {
        runtime_error_thrown = true;
        error_msg = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_msg == "cannot pop from empty LinkedList");    
}

// See if popFromFront() correctly removes first element of multichar list
// and shifts remaining elements over by 1.
void pop_front_multichar_list() {
    char items[] = {'a','b','c','d','e','f'};
    CharLinkedList list(items, 6);

    list.popFromFront();

    assert(list.toString() == "[CharLinkedList of size 5 <<bcdef>>]");
}

// See if popFromFront() correctly removes the element of a one-char list
void pop_front_onechar_list() {
    CharLinkedList list('a');

    list.popFromFront();

    assert(list.isEmpty());
}

// elementAt() TESTS

// See if elementAt() correctly throws std::range_error and appropriate
// message when given an empty list
void element_at_empty_arr() {
    CharLinkedList list;
    bool range_error_thrown = false;

    std::string error_msg = "";

    try {
        list.elementAt(2);
    }
    catch (std::range_error &e) {
        range_error_thrown = true;
        error_msg = e.what();
    }

    assert(range_error_thrown);
    assert(error_msg == "index (2) not in range [0..0)");
}

// See if elementAt() correctly throws std::range_error and appropriate
// message when given an index out of range of the given list
void element_at_invalid_index() {
    char items[] = {'a','b','c'};
    CharLinkedList list(items, 3);
    bool range_error_thrown = false;

    std::string error_msg = "";

    try {
        list.elementAt(4);
    }
    catch (std::range_error &e) {
        range_error_thrown = true;
        error_msg = e.what();
    }

    assert(range_error_thrown);
    assert(error_msg == "index (4) not in range [0..3)");
}

// See if elementAt() correctly throws std::range_error and appropriate 
// message when given a negative index
void element_at_negative_index() {
    char items[] = {'a','b','c'};
    CharLinkedList list(items, 3);
    bool range_error_thrown = false;

    std::string error_msg = "";

    try {
        list.elementAt(-7);
    }
    catch (std::range_error &e) {
        range_error_thrown = true;
        error_msg = e.what();
    }

    assert(range_error_thrown);
    assert(error_msg == "index (-7) not in range [0..3)");
}

// See if elementAt() works when given a valid index in a multichar list
void element_at_valid_index_multichar() {
    char items[] = {'a','b','c'};
    CharLinkedList list(items, 3);
    // char returned = list.elementAt(2);

    assert(list.elementAt(2) == 'c');
}

// See if elementAt() works when given a valid index in a single-char list
void element_at_valid_index_singlechar() {
    CharLinkedList list('a');
    char returned = list.elementAt(0);

    assert(returned == 'a');
}

// clear() TESTS

// Checks if clear() functions correctly with an empty list 
// (i.e. no errors) and that the list is still empty
void clear_blank_list() {
    CharLinkedList list;

    list.clear();
    assert(list.isEmpty());
}

// Checks if clear() functions correctly for a one char list
void clear_onechar_list() {
    CharLinkedList list('a');

    list.clear();
    assert(list.isEmpty());
}

// Checks if clear() functions correctly for an list with chars by
// ensuring isEmpty() returns true after it is cleared.
void clear_multi_char_list() {
    char items[] = {'a','b','c'};
    CharLinkedList list(items, 3);
    assert(list.size() == 3);
    list.clear();

    assert(list.isEmpty());

}

// removeAt() TESTS

// Tests to ensure calling removeAt on empty list returns range error
void removeAt_empty() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList test_list;
    try {
    // insertAt for out-of-range index
        test_list.removeAt(2);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..0)");
    
}

// Tests correct removeAt for front of 1-element list.
void removeAt_front_singleton_list() {
    
    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at front
    test_list.removeAt(0);

    assert(test_list.isEmpty()); 
}

// Tests calling removeAt for a large number of elements.
// Not only does this test removeAt, it also checks that
// list expansion works correctly.
void removeAt_many_elements() {
    
    CharLinkedList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    for (int i = 0; i < 1000; i++) {
        test_list.removeAt(0);
    }

    assert(test_list.isEmpty());
}

// Tests removal in front of a larger list
void removeAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 9);

    test_list.removeAt(0);

    assert(test_list.size() == 8);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.toString() == "[CharLinkedList of size 8 <<bczdefgh>>]");

}

// Tests removal in the back of a larger list
void removeAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 10);  

    test_list.removeAt(9);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(8) == 'g');
    assert(test_list.toString() == 
    "[CharLinkedList of size 9 <<yabczdefg>>]"); 

}

// Tests removal in the middle of a larger list
void removeAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    test_list.removeAt(3);

    assert(test_list.size() == 7);
    assert(test_list.elementAt(3) == 'e');
    assert(test_list.toString() == "[CharLinkedList of size 7 <<abcefgh>>]");

}

// Tests out-of-range removal for a non-empty list.
void removeAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8)");
    
}

// first() TESTS

// Checks if first returns the first element of the list in a 1-char
// list
void first_one_char_list() {
    CharLinkedList list('a');

    assert(list.first() == 'a');
}

// Checks if first returns the first element of the list in a multi-char
// list
void first_multi_char_list() {
    char items[] = {'b','c','d'};
    CharLinkedList list(items, 3);

    assert(list.first() == 'b');
}

// Checks if first throws the runtime_error exception for an empty list
// and prints the proper error message
void first_empty_list() {
    CharLinkedList list;
    bool runtime_error_thrown = false;

    std::string error_message = "";

    try {
        list.first();
    }
    catch (std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

// Ensure first() works after changing first element of a list
void first_modified_list() {
    char items[] = {'b','c','d'};
    CharLinkedList list(items, 3);

    assert(list.first() == 'b'); 

    list.pushAtFront('z');

    assert(list.first() == 'z');
}

// last() TESTS
// Checks if last returns the element of a 1-char list
void last_one_char_list() {
    CharLinkedList list('a');

    assert(list.last() == 'a');
}

// Checks if last returns the last element of a multi-char list
void last_multi_char_list() {
    char items[] = {'a','b','c'};
    CharLinkedList list(items, 3);

    assert(list.last() == 'c');
}

// Checks if last throws a runtime_error exception when used on empty list
void last_empty_list() {
    CharLinkedList list;
    bool runtime_error_thrown = false;

    std::string error_message = "";

    try {
        list.last();
    }
    catch (std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}  

// Ensure last() works after changing last element of a list twice
void last_modified_list() {
    char items[] = {'b','c','d'};
    CharLinkedList list(items, 3);

    assert(list.last() == 'd'); 

    list.popFromBack();
    list.popFromBack();
    assert(list.last() == 'b');
}

// COPY CONSTRUCTOR TESTS

// Ensures an empty list is correctly copied w/ copy constructor
void copy_constructor_empty_arr() {
    CharLinkedList list1;

    assert(list1.isEmpty());

    CharLinkedList list2(list1);

    assert(list2.isEmpty());

}

// Ensures a multichar list is correctly copied with copy constructor
void copy_constructor_multichar_arr() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);

    CharLinkedList list2(list1);

    // Insert char in original list
    list1.insertAt('z', 0);

    // If copy constructor made a deep copy correctly, 'z' should not appear
    // in list2.
    assert(list1.elementAt(0) == 'z');
    assert(list2.elementAt(0) != 'z');
}


// Ensure using replaceAt() on empty list returns range error
void replace_at_empty_arr() {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList test_list;
    try {
    // insertAt for out-of-range index
    test_list.replaceAt('a', 0);
    }
    catch (const std::range_error &e) {

    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// Ensure replaceAt() works on first element of multichar list
void replace_at_first_multichar() {
    char items[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    CharLinkedList list(items, 6);

    list.replaceAt('z', 0);

    assert(list.toString() == "[CharLinkedList of size 6 <<zbcdef>>]");
}

// Ensure replaceAt() works on last element of multichar list
void replace_at_last_multichar() {
    char items[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    CharLinkedList list(items, 6);

    list.replaceAt('z', 5);

    assert(list.toString() == "[CharLinkedList of size 6 <<abcdez>>]");
}

// Ensure replaceAt() works on middle element of multichar list
void replace_at_middle_multichar() {
    char items[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    CharLinkedList list(items, 6);

    list.replaceAt('z', 2);

    assert(list.toString() == "[CharLinkedList of size 6 <<abzdef>>]");
}

// Ensure replaceAt() works on one-char list
void replace_at_onechar_list() {
    CharLinkedList list('a');  

    list.replaceAt('z', 0);

    assert(list.elementAt(0) == 'z');
}

// concatenate() TESTS

// Ensure concatenate works on blank list with iself
void concat_blank_list_self() {
    CharLinkedList list1;

    list1.concatenate(&list1);

    assert(list1.toString() == "[CharLinkedList of size 0 <<>>]");
    assert(list1.size() == 0);
}

// Ensure concatenate works on two different multichar lists
void concat_multichar_list() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);
    char items2[] = {'d','e','f'};
    CharLinkedList list2(items2, 3);

    list1.concatenate(&list2);

    assert(list1.toString() == "[CharLinkedList of size 6 <<abcdef>>]");
    assert(list1.size() == 6);
}

// Ensure concatenate works on multichar list with itself
void concat_multichar_list_with_self() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);

    list1.concatenate(&list1);

    assert(list1.toString() == "[CharLinkedList of size 6 <<abcabc>>]");
    assert(list1.size() == 6);
}



// Ensure concatenate works on multichar list with blank list
void concat_multichar_list_with_blank() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);
    CharLinkedList list2;

    list1.concatenate(&list2);

    assert(list1.toString() == "[CharLinkedList of size 3 <<abc>>]");
    assert(list1.size() == 3);
}

// Assignment Operator TEST

// Ensure assignment operator properly produces a deep copy
void assignment_operator_multichar_list() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);

    CharLinkedList list2;

    list2 = list1;

    // Insert char in original list
    list1.insertAt('z', 0);

    // If assignment operator made a deep copy correctly, 'z' should not appear
    // in list2.
    assert(list1.elementAt(0) == 'z');
    assert(list2.elementAt(0) != 'z');
}

// Ensure assignment operator used on itself returns itself (no errors)
void assignment_operator_multichar_self() {
    char items[] = {'a','b','c'};
    CharLinkedList list1(items, 3);

    list1 = list1;
    assert(list1.size() == 3);
}