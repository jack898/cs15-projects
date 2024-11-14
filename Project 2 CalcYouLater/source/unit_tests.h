/*
 *  unit_tests.h
 *  Jack Burton
 *  10/12/2023
 *
 *  CS 15 Proj 2 CalcYouLater
 *
 *  Uses Matt Russell's unit_test framework to test CalcYouLater.
 *
 */

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"

/******************************************************************************/
/*  DatumStack Class Tests                                                    */
/******************************************************************************/

// OVERLOADED CONSTRUCTOR TESTS
// Confirms that DatumStack overloaded constructor works with an array of 
// every type of Datum
void overloaded_constructor_varying_values() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum arr[] = {a, b, c};
    DatumStack d(arr, 3); // create DatumStack with array of Datums of all types

    assert(d.size() == 3);
    assert(d.top() == c); // top element of DatumStack is "hello world"
}

// isEmpty() TESTS
// Confirms that isEmpty() works on empty DatumStack
void isEmpty_empty_stack() {
    DatumStack a;

    assert(a.isEmpty());
}

// Confirms that isEmpty() works on filled, and then empty DatumStack
void isEmpty_nonempty_then_empty_stack() {
    Datum a(1);
    DatumStack stack;
    assert(stack.isEmpty()); // stack should be empty
    
    stack.push(a);
    assert(not stack.isEmpty()); // stack shouldn't be empty

}

// clear() TESTS
// Confirms that clear() works on a DatumStack with multiple elements
void clear_multiple_element_stack() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum arr[] = {a, b, c};
    DatumStack d(arr, 3); // create DatumStack with array of Datums of all types
    
    assert(not d.isEmpty()); // stack should have elements
    d.clear();

    assert(d.isEmpty());
}


// Confirms that clear() works (no errors) on an empty DatumStack
void clear_empty_stack() {
    DatumStack stack;
    stack.clear();
    assert(stack.isEmpty());
}

// size() TESTS
// Confirms that size() works on a multiple element DatumStack
void size_multielement_stack() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 

    assert(stack.size() == 5);
}

// Confirms that size() works on an empty DatumStack
void size_empty_stack() {
    DatumStack stack;
    assert(stack.size() == 0);
}

// Confirms that size() works on a DatumStack that changes size
void size_changing_stack() {
    DatumStack stack;
    Datum a(1);
    assert(stack.size() == 0);

    stack.push(a);
    assert(stack.size() == 1);
}

// top() TESTS

// Confirms that top() throws empty_stack error for empty stack
void top_empty_stack() {
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    DatumStack stack;
    try {
        Datum a = stack.top();
    }
    catch (const std::runtime_error &e) {

    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");  
}

// Confirms that top returns top of stack with multiple items, when top 
// changes 
void top_multielement_stack() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 
    
    Datum top = stack.top();
    assert(top == e);

    stack.pop(); // remove top element
    top = stack.top();
    assert(top == d); // top should be d now
}

// pop() TESTS

// Confirms that pop() throws empty_stack error for empty stack
void pop_empty_stack() {
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;
    // var to track any error messages raised
    std::string error_message = "";

    DatumStack stack;
    try {
        stack.pop();
    }
    catch (const std::runtime_error &e) {

    runtime_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");  
}

// Confirms that pop() works on a stack with multiple elements
void pop_multielement_stack() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 
    
    assert(stack.size() == 5);
    stack.pop();
    assert(stack.size() == 4);
    assert(stack.top() == d);
}

// Confirms that pop() works on a stack w multiple elements until empty
void pop_multielement_stack_until_empty() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 
    
    assert(stack.size() == 5);
    for (int i = 0; i < 5; i++) {
        stack.pop();
    }

    assert(stack.isEmpty());
}

// push() TESTS

// Confirms that push() works on an empty stack
void push_empty_stack() {
    Datum a(1);
    DatumStack stack;
    assert(stack.isEmpty());

    stack.push(a);
    assert(stack.size() == 1);
    assert(stack.top() == a);
}

// Confirms that push() allows pushing new datum onto multiple element stack
void push_multielement_stack_new_datum() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 
    
    assert(stack.size() == 5);
    assert(stack.top() == e);

    Datum f(2); // create new Datum and push to stack
    stack.push(f);
    assert(stack.size() == 6);
    assert(stack.top() == f);

    Datum g(2); // create another new Datum and push to stack
    stack.push(g);
    assert(stack.size() == 7);
    assert(stack.top() == g);
    
}

// Confirms that push() allows pushing same datum multiple times onto
// multiple element stack
void push_multielement_stack_same_datum() {
    Datum a(1);
    Datum b(true);
    Datum c("hello world");
    Datum d(true);
    Datum e(false);
    Datum arr[] = {a, b, c, d, e};
    // create DatumStack with array of Datums of all types
    DatumStack stack(arr, 5); 
    
    assert(stack.size() == 5);
    stack.push(a);
    assert(stack.size() == 6);
    assert(stack.top() == a);
}



/******************************************************************************/
/*  Parser Class Tests                                                        */
/******************************************************************************/

// parseRString() TESTS
// Confirms that parseRString() works on a normal rString
void parseRString_normal_string() {
    std::string rString = "1 2 3 4 5 }";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == "{ 1 2 3 4 5 }");
}

// Confirms that parseRString() works on an empty rString
void parseRString_empty_string() {
    std::string rString = "}";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == "{ }");
}

// Confirms that parseRString() gets rid of extra spaces
void parseRString_extra_spaces() {
    std::string rString = "     \n    1 \n\n     2 +      }";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == "{ 1 2 + }");
}

// Confirms that parseRString() works on an rstring with words
void parseRString_words() {
    std::string rString = "hello { world 123 } hello world hello world }";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == "{ hello { world 123 } hello world hello world }");
}

// Confirms that parseRString() works on a complex rstring with
// multiple nested rstrings
void parseRString_multi_nest() {
    std::string rString = 
    "one two { 1 + 2 } { cha cha cha } { 3 + 4 } { cha cha cha } }";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == 
    "{ one two { 1 + 2 } { cha cha cha } { 3 + 4 } { cha cha cha } }");
}

// Confirms that parseRString() works when ints given after rstring
void parseRString_ints_after_string() {
    std::string rString = "1 1 + } 4 2";
    std::stringstream input(rString);
    std::string parsedRString = parseRString(input);
    assert(parsedRString == "{ 1 1 + }");
}


/******************************************************************************/
/*  RPNCalc Class Tests                                                       */
/******************************************************************************/

// Confirms that RPNCalc constructor and destructor work
void RPNCalc_construct_destruct() {
    RPNCalc instance;
}

// run() TESTS

// Ensure run() throws thank you message and exits at end of cin
// (manually checked since run() feeds to cout)
// (also will throw ": unimplemented" because of no cin given)
void run_quit_command() {
    RPNCalc instance;
    instance.run();
}


// processCommand() TESTS
// NOTE: Many of these functions go to stdout, so cannot be asserted for
// unit testing. Stdout from unit_test will be checked manually for each
// function, and diff testing will be performed against theCalcYouLater
// for sequences of commands.

// TYPING AN INT
// Ensure that typing one int adds it to the stack properly (no errors)
void add_one_int() {
    RPNCalc instance;
    stringstream ss ("4");
    instance.processCommand(ss);
}

// Ensure that typing multiple ints adds them all to stack (no errors)
void add_multiple_ints() {
    RPNCalc instance;
    stringstream ss ("4 5 6");
    instance.processCommand(ss);
}

// TYPING A BOOL
// Ensure that typing #t or #f adds the bool to the stack properly (no errors)
void add_one_bool() {
    RPNCalc instance;
    stringstream ss ("#t");
    instance.processCommand(ss);

    stringstream ss2 ("#f");
    instance.processCommand(ss2);
}

// Ensure that typing multiple bools adds them all to stack properly (no errors)
void add_multiple_bools() {
    RPNCalc instance;
    stringstream ss ("#t #f #t #t #f");
    instance.processCommand(ss);
}

// TYPING AN RSTRING
// Ensure that typing an rString adds it to the stack properly (no errors)
void add_one_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 1 2 3 { 1 2 + } }");
    instance.processCommand(ss);
}

// Ensure that adding two rStrings to the stack works properly (no errors)
void add_two_rstrings() {
    RPNCalc instance;
    stringstream ss ("{ 1 2 3 { 1 2 + } } { 1 2 3 { 1 2 + } }");
    instance.processCommand(ss);
}


// NOT
// Ensure that not() correctly flips bool at top of stack
// (Manually check that stdout is #f)
void not_valid_stack() {
    RPNCalc instance;
    stringstream ss ("#t not print");
    instance.processCommand(ss);
}

// Ensure that not() throws empty_stack error for an empty stack
// (Manually check that stdout is Error: empty_stack)
void not_empty_stack() {
    RPNCalc instance;
    stringstream ss ("not");
    instance.processCommand(ss);
}

// Ensure that not() throws datum_not_bool error for a stack without 
// a bool on top
// (Manually check that stdout is Error: datum_not_bool)
void not_no_bool() {
    RPNCalc instance;
    stringstream ss ("4 not");
    instance.processCommand(ss);
}

// PRINT
// Ensure that print prints a true and false bool properly
// (Manually check that stdout is #t \n #f)
void print_bools() {
    RPNCalc instance;
    stringstream ss ("#t print #f print");
    instance.processCommand(ss);
}

// Ensure that print prints an int properly
// (Manually check that stdout is 4)
void print_int() {
    RPNCalc instance;
    stringstream ss ("4 print");
    instance.processCommand(ss);
}

// Ensure that print prints an rString properly
// (Manually check that stdout is { 1 2 3 { 1 2 + } })
void print_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 1 2 3 { 1 2 + } } print");
    instance.processCommand(ss);
}

// CLEAR
// Ensure that clear() clears a stack properly
// (Manually check that stderr contains stack_empty error--i.e.
// clear got rid of 1 2 3)
void clear_stack() {
    RPNCalc instance;
    stringstream ss ("1 2 3 clear print");
    instance.processCommand(ss);
}

// DROP
// Ensure that drop drops multiple elements from a stack properly
// (Manually check that stderr contains stack_empty error--i.e. drop got rid
// of all elements and then threw that error)
void drop_multiple_elements() {
    RPNCalc instance;
    stringstream ss ("1 2 3 drop drop drop drop");
    instance.processCommand(ss);
}


// DUP
// Ensure that dup duplicates top element from a stack properly
void dup_one_element() {
    RPNCalc instance;
    stringstream ss ("1 dup print");
    instance.processCommand(ss);
}

// SWAP
// Ensure that swap swaps top two elements from a stack properly
// (Manually check that stdout is 1)
void swap_elements() {
    RPNCalc instance;
    stringstream ss ("1 2 swap print");
    instance.processCommand(ss);
}

// Ensure that swap throws empty_stack error for an empty stack
// (Manually check that stderr is Error: empty_stack)
void swap_empty_stack() {
    RPNCalc instance;
    stringstream ss ("swap");
    instance.processCommand(ss);
}

// Ensure that swap throws empty_stack error for a stack with 1 element
// (Manually check that stderr is 2 x Error: empty_stack for swap and
// when trying to print element that should be gone)
void swap_one_element_stack() {
    RPNCalc instance;
    stringstream ss ("1 swap print");
    instance.processCommand(ss);
}

// QUIT
// Ensure that quit exits program properly with thank you msg
// (Manually check that stdout is Thank you for using CalcYouLater!)
void quit_command() {
    RPNCalc instance;
    stringstream ss ("quit");
    instance.processCommand(ss);
}

// ADDITION
// Ensure that addition works for two ints on stack
// (Manually check that stdout is 3)
void add_two_ints() {
    RPNCalc instance;
    stringstream ss ("1 2 + print");
    instance.processCommand(ss);
}

// Ensure that addition throws empty_stack error for an insufficient stack
// (Manually check that stderr is Error: empty_stack)
void add_error_situation() {
    RPNCalc instance;
    stringstream ss ("1 + print");
    instance.processCommand(ss);
}

// SUBTRACTION
// Ensure that subtraction works for two ints on stack
// (Manually check that stdout is 1)
void subtract_two_ints() {
    RPNCalc instance;
    stringstream ss ("2 1 - print");
    instance.processCommand(ss);
}

// Ensure that subtraction throws empty_stack error for an insufficient stack
// (Manually check that stderr is Error: empty_stack)
void subtract_error_situation() {
    RPNCalc instance;
    stringstream ss ("1 - print");
    instance.processCommand(ss);
}

// MULTIPLICATION
// Ensure that multiplication works for two ints on stack
// (Manually check that stdout is 35)
void multiply_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 7 * print");
    instance.processCommand(ss);
}

// Ensure that multiplication works for large ints on stack
// (Manually check that stdout is 100000000)
void multiply_large_ints() {
    RPNCalc instance;
    stringstream ss ("10000 10000 * print");
    instance.processCommand(ss);
}

// DIVISION
// Ensure that division works for two ints on stack
// (Manually check that stdout is 2)
void divide_two_ints() {
    RPNCalc instance;
    stringstream ss ("4 2 / print");
    instance.processCommand(ss);
}

// Ensure that division throws Error: division by zero when trying to divide
// by zero
// (Manually check that stderr is Error: division by zero)
void divide_by_zero() {
    RPNCalc instance;
    stringstream ss ("4 0 / print");
    instance.processCommand(ss);
}

// MODULO
// Ensure that mod works properly for two ints on stack
// (Manually check that stdout is 1)
void mod_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 mod print");
    instance.processCommand(ss);
}

// Ensure that mod throws Error: division by zero when trying to mod by zero
// (Manually check that stderr is Error: division by zero)
void mod_by_zero() {
    RPNCalc instance;
    stringstream ss ("4 0 mod print");
    instance.processCommand(ss);
}

// GREATER THAN
// Ensure that greater than works properly for greater than equation with true
// result
// (Manually check that stdout is #t)
void greater_than_true_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 > print");
    instance.processCommand(ss);
}

// Ensure that greater than works properly for greater than equation with 
// false result
// (Manually check that stdout is #f)
void greater_than_false_two_ints() {
    RPNCalc instance;
    stringstream ss ("2 5 > print");
    instance.processCommand(ss);
}

// LESS THAN
// Ensure that less than works properly for true less than comparison
// (Manually check that stdout is #t)
void less_than_true_two_ints() {
    RPNCalc instance;
    stringstream ss ("2 5 < print");
    instance.processCommand(ss);
}

// Ensure that less than works properly for false less than comparison
// (Manually check that stdout is #f)
void less_than_false_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 < print");
    instance.processCommand(ss);
}

// GREATER THAN OR EQUAL TO
// Ensure that greater than or equal to works properly for true comparison
// (Manually check that stdout is #t)
void greater_than_or_equal_to_true_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 >= print");
    instance.processCommand(ss);
}

// Ensure that greater than or equal to works properly for false comparison
// (Manually check that stdout is #f)
void greater_than_or_equal_to_false_two_ints() {
    RPNCalc instance;
    stringstream ss ("2 5 >= print");
    instance.processCommand(ss);
}

// Ensure that greater than or equal to works properly for equal (true) 
// comparison
// (Manually check that stdout is #t)
void greater_than_or_equal_to_equal_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 5 >= print");
    instance.processCommand(ss);
}

// LESS THAN OR EQUAL TO
// Ensure that less than or equal to works properly for true comparison
// (Manually check that stdout is #t)
void less_than_or_equal_to_true_two_ints() {
    RPNCalc instance;
    stringstream ss ("2 5 <= print");
    instance.processCommand(ss);
}

// Ensure that less than or equal to works properly for false comparison
// (Manually check that stdout is #f)
void less_than_or_equal_to_false_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 <= print");
    instance.processCommand(ss);
}

// Ensure that less than or equal to works properly for equal (true)
// comparison (Manually check that stdout is #t)
void less_than_or_equal_to_equal_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 5 <= print");
    instance.processCommand(ss);
}

// EQUAL TO
// Ensure that equal to works properly for true (equal) comparison
// (Manually check that stdout is #t)
void equal_to_true_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 5 == print");
    instance.processCommand(ss);
}

// Ensure that equal to works properly for false (non-equal) comparison
// (Manually check that stdout is #f)
void equal_to_false_two_ints() {
    RPNCalc instance;
    stringstream ss ("5 2 == print");
    instance.processCommand(ss);
}

// EXEC
// Ensure that exec works on a simple rString equation
// (Manually check that stdout is 4)
void exec_simple_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 1 3 + } exec print");
    instance.processCommand(ss);
}

// Ensure that exec works on a nested rString
// (Manually check that stdout is { 1 2 } \n 1)
void exec_nested_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 1 { 1 2 } } exec print drop print");
    instance.processCommand(ss);
}

// Ensure that exec throws error msg for non rstring
// (Manually check that stderr is Error: cannot execute non rstring)
void exec_non_rstring() {
    RPNCalc instance;
    stringstream ss ("1 exec");
    instance.processCommand(ss);
}

// Ensure that exec works for long rString with many operations
// (Manually check that stdout is 14)
void exec_long_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 5 1 2 + 4 * + 3 - } exec print");
    instance.processCommand(ss);
}

// Ensure that exec works for an rString with an improper command
// (Manually check that stderr is Error: datum_not_int)
void exec_error_rstring() {
    RPNCalc instance;
    stringstream ss ("{ 1 #t + } exec");
    instance.processCommand(ss);
}   

// FILE
/* File function was tested manually by utilizing pre-made .cylc files and
 * creating new ones to test various situations, and then diff testing these
 * results against theCalcYouLater. See README for more information.
*/

// IF
// Ensure that if throws correct error if no bool for test condition
// (Manually check that stderr is Error: expected rstring in if branch)
void if_no_bool() {
    RPNCalc instance;
    stringstream ss ("1 { 1 } { 1 } if");
    instance.processCommand(ss);
}


// Ensure that if throws correct error if no rString for true branch
// (Manually check that stderr is Error: expected rstring in if branch)
void if_no_rstring_true() {
    RPNCalc instance;
    stringstream ss ("#t 1 { 1 } if");
    instance.processCommand(ss);
}

// Ensure that if throws correct error if no rString for false branch
// (Manually check that stderr is Error: expected rstring in if branch)
void if_no_rstring_false() {
    RPNCalc instance;
    stringstream ss ("#f { 1 } 1 if");
    instance.processCommand(ss);
}

// Ensure that if works correctly for test condition true
// (Manually check that stdout is 1)
void if_test_condition_true() {
    RPNCalc instance;
    stringstream ss ("#t { 1 } { 2 } if print");
    instance.processCommand(ss);
}

// Ensure that if works correctly for test condition false
// (Manually check that stdout is 2)
void if_test_condition_false() {
    RPNCalc instance;
    stringstream ss ("#f { 1 } { 2 } if print");
    instance.processCommand(ss);
}

// Ensure that if works correctly for nested rstring in case executed
// (Manually check that stdout is { 2 })
void if_nested_rstring() {
    RPNCalc instance;
    stringstream ss ("#t { 1 { 1 } } { 2 } if exec print");
    instance.processCommand(ss);
}
 
 





