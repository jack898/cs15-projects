/*
 *  CharLinkedList.cpp
 *  Jack Burton
 *  9/20/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Implement the CharLinkedList class functions.
 *
 */

#include "CharLinkedList.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList node
 * arguments: none
 * returns:   none
 * effects:   front and back pointers, numItems int
 */
CharLinkedList::CharLinkedList() {
    numItems = 0;
    front = nullptr;
    back = nullptr;
}

/* 
 * name:      CharLinkedList one char constructor
 * purpose:   initialize a CharLinkedList with one element
 * arguments: char element
 * returns:   none
 * effects:   numItems, data for a new Node
 */
CharLinkedList::CharLinkedList(char c) {
    numItems = 1;
    front = newNode(c, nullptr, nullptr);
    back = front; // the one element is both the front and back node
}

/* 
 * name:      CharLinkedList multi char constructor
 * purpose:   initialize a CharLinkedList with multiple elements
 * arguments: array of chars, int w size of that array
 * returns:   none
 * effects:   numItems, data/prev/next for each new node
 */
CharLinkedList::CharLinkedList(char arr[], int size) {
    numItems = size;
    Node *first = newNode(arr[0], nullptr, nullptr);
    back = front = first;
    
    for (int i = 1; i < numItems; i++) {
        Node *nextNode = newNode(arr[i], first, nullptr);
        back = nextNode; // this is the new back of the list
        first->next = nextNode;
        first = nextNode;
    }
    back->next = nullptr;
}

/* 
 * name:      CharLinkedList copy constructor
 * purpose:   create a deep copy of given CharLinkedList instance
 * arguments: reference to another CharLinkedList
 * returns:   none
 * effects:   numItems, front, back for new CharLinkedList copy, data/prev/next
 * for new nodes in copy
*/
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    front = back = nullptr;
    numItems = 0; // updated by pushAtBack appropriately

    Node *curr = other.front;
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(curr->data);
        curr = curr->next;
    }
}

/*  
 * name:      CharLinkedList assignment operator
 * purpose:   copies other list into lhs list
 * arguments: reference to another CharLinkedList to be copied
 * returns:   pointer to a CharLinkedList
 * effects:   numItems, front, back for new CharLinkedList copy, data/prev/next
 * for new nodes in copy
*/
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other) {
    if (this == &other) {
        return *this;
    }
    front = back = nullptr;
    numItems = 0;
    Node *curr = other.front;
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(curr->data);
        curr = curr->next;
    }

    return *this;
}



/* 
 * name:      replaceAt
 * purpose:   replaces char at a node with a different char
 * arguments: a char element and an int with index
 * returns:   none
 * effects:   node at specified index
 */
void CharLinkedList::replaceAt(char c, int index) {
    if (index > size() or index < 0 or isEmpty()) {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << ")";
        throw std::range_error(ss.str());
    }  

    // recursively finds the node to replace char at
    Node *nodeToReplace = elementFinder(index, front);
    nodeToReplace->data = c;
}


/*
 * name:      concatenate
 * purpose:   adds a copy of other list to list that function is called from
 * arguments: pointer to other list
 * returns:   none
 * effects:   next pointer for back of callee list, numItems for callee list
*/
void CharLinkedList::concatenate(CharLinkedList *other) {
    int otherSize = other->size();
    
    Node *curr = other->front;

    for (int i = 0; i < otherSize; i++) {
        pushAtBack(curr->data); // add other items to back of callee list
        curr = curr->next;
    }
}

/* 
 * name:      toString
 * purpose:   convert a CharLinkedList to a properly formatted string
 * arguments: none
 * returns:   string containing all chars from CharLinkedList
 * effects:   none
 */
std::string CharLinkedList::toString() const {
    std::stringstream ss;

    ss << "[CharLinkedList of size " << size() << " <<";

    Node *curr = front;
    for (int i = 0; i < numItems; i++) {
        ss << curr->data;
        curr = curr->next;
    }

    ss << ">>]";

    return ss.str();
}

/* 
 * name:      toReverseString
 * purpose:   convert a CharLinkedList to a properly formatted backwards string
 * arguments: none
 * returns:   string containing all chars from CharLinkedList in reverse
 * order
 * effects:   none
 */
std::string CharLinkedList::toReverseString() const {
    std::stringstream ss;

    ss << "[CharLinkedList of size " << size() << " <<";

    Node *curr = back; // start at the back to go thru in reverse
    for (int i = 0; i < numItems; i++) {
        ss << curr->data;
        curr = curr->prev;
    }

    ss << ">>]";

    return ss.str();
}

/* 
 * name:      popFromBack
 * purpose:   remove node at back of the list
 * arguments: none
 * returns:   none
 * effects:   prev and next for prev node before back
 */
void CharLinkedList::popFromBack() {
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }

    removeAt(size() - 1);
}

/* 
 * name:      popFromFront
 * purpose:   remove node at front of the list
 * arguments: none
 * returns:   none
 * effects:   prev and next for next node after front
 */
void CharLinkedList::popFromFront() {
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }

    removeAt(0);
}



/* 
 * name:      pushAtFront
 * purpose:   insert a node into the CharLinkedList at front of the list
 * arguments: char for a new node
 * returns:   none
 * effects:   data, prev, and next for a new node
 */
void CharLinkedList::pushAtFront(char c) {
    numItems++;
    front = newNode(c, nullptr, front);
}

/* 
 * name:      pushAtBack
 * purpose:   insert a node into the CharLinkedList at back of the list
 * arguments: char for a new node
 * returns:   none
 * effects:   data, prev, and next for a new node
 */
void CharLinkedList::pushAtBack(char c) {
    numItems++;
    back = newNode(c, back, nullptr);
    if (size() == 1) { // skip the reassigning prev back if list was empty
        front = back;
        return;
    }
    back->prev->next = back;
}

/* 
 * name:      insertAt
 * purpose:   insert a node into the CharLinkedList at specified index
 * arguments: index in CharLinkedList, char for a new node
 * returns:   none
 * effects:   new node's data, prev, and next, as well as surrounding nodes'
 * next and prev values
 */
void CharLinkedList::insertAt(char c, int index) {
    if (index > size() or index < 0) {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << "]";
        throw std::range_error(ss.str());
    }

    if (index == 0) { // edge case for front element
        pushAtFront(c);
        return;
    }

    int count = 0;
    Node *curr = front;
    while (count != index - 1) {
        count++;
        curr = curr->next;
    }

    numItems++;
    if (curr == back) { // edge case for back element
        curr->next = back = newNode(c, curr, nullptr);
    } 
    else {
    curr->next = newNode(c, curr, curr->next);
    }
}

/* 
 * name:      insertInOrder
 * purpose:   insert a node into the CharLinkedList at ASCII-ordered correct
 * index
 * arguments: char for a new node
 * returns:   none
 * effects:   new node's data, prev, and next, as well as surrounding nodes'
 * next and prev values
 */
void CharLinkedList::insertInOrder(char c) {
    bool inserted = false;
    Node *curr = front;
    for (int i = 0; i < numItems; i++) {
        if (c <= curr->data) {
            insertAt(c, i);
            inserted = true;
            return;
        }
        curr = curr->next;
    }
    if (not inserted) {
        pushAtBack(c);
    }
}

/* 
 * name:      elementAt
 * purpose:   return the char at a specified index in the linked list
 * arguments: index
 * returns:   char from node at arg index
 * effects:   none
 */
char CharLinkedList::elementAt(int index) const {
    if (isEmpty() or (index > numItems - 1 or index < 0)) { // catch edge cases
        std::stringstream err;
        err << "index (" << index << ") not in range [0.." << size() << ")";
        throw std::range_error(err.str());
    }
    Node *nodeAtIndex = elementFinder(index, front); // call recursive helper
    return nodeAtIndex->data;
}

/* 
 * name:      elementFinder
 * purpose:   return the char at a specified index in the linked list
 * arguments: index int, pointer to a node
 * returns:   char from node at arg index
 * effects:   none
 */
CharLinkedList::Node *CharLinkedList::elementFinder(int ind, Node *curr) const {
    if (ind == 0) { // base case
        return curr;
    }
    else {
        return elementFinder(ind - 1, curr->next); 
    }
}

/* 
 * name:      clear
 * purpose:   makes the list into an empty list
 * arguments: none
 * returns:   none
 * effects:   each node in linked list
 */
void CharLinkedList::clear() {
    Node *curr = front;
    while (curr != nullptr) {
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }
    front = nullptr;

    numItems = 0;
}

/* 
 * name:      removeAt
 * purpose:   removes node at specified index and shifts previous/next for
 * surrounding nodes accordingly
 * arguments: index in charlinkedlist
 * returns:   none
 * effects:   node at index, prev/next values for surrounding nodes
 */
void CharLinkedList::removeAt(int index) {
    if (index > size() or index < 0) {
        std::stringstream ss;
        ss << "index (" << index << ") not in range [0.." << size() << ")";
        throw std::range_error(ss.str());
    }
    Node *curr = front;
    int count = 0;
    while (count < index) {
        curr = curr->next;
        count++;
    }

    removeAtHelper(curr); // reset surrounding node values via location in list
    numItems--;
    delete curr;
}

/* 
 * name:      removeAtHelper
 * purpose:   helper to reset surrounding node values depending on location
 * in linked list
 * arguments: pointer to a node object
 * returns:   none
 * effects:   prev and next values for surrounding node(s)
 */
void CharLinkedList::removeAtHelper(Node *curr) {
    if (size() == 1) { // edge case for one-char list
        front = back = nullptr;
    }
    else if (curr == front) {
        curr->next->prev = nullptr;
        front = curr->next;
    }
    else if (curr == back) {
        curr->prev->next = nullptr;
        back = curr->prev;
    }
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
}



/* 
 * name:      newNode
 * purpose:   helper to create a new node in a CharLinkedList
 * arguments: char element, pointer to previous element, pointer to next element
 * returns:   Node object
 * effects:   data, prev, next for a new node
 */
CharLinkedList::Node *CharLinkedList::newNode
(char newData, Node *prev, Node *next) {
    Node *new_node = new Node;
    new_node->data = newData;
    new_node->next = next;
    new_node->prev = prev;
    if (next != nullptr) { // ensure not at the end of linked list
        new_node->next->prev = new_node;
    }

    return new_node;   
}



/*
 * name:      CharLinkedList destructor
 * purpose:   calls helper to recursively recycle CharLinkedList
 * memory.
 * arguments: none
 * returns:   none
 * effects:   none
 */
CharLinkedList::~CharLinkedList() {
    recycleRecursive(front);
}

/*
 * name:      recycleRecursive
 * purpose:   helper to recursively delete nodes on linked list
 * arguments: pointer to a node in the linked list
 * returns:   none
 * effects:   each node by deleting its memory
 */
void CharLinkedList::recycleRecursive(Node *curr) {
    if (curr == nullptr) { // base case
        return;
    }
    else { // recursive case
        recycleRecursive(curr->next);
        delete curr;
    }
}

/*
 * name:      size
 * purpose:   returns size of a CharLinkedList
 * arguments: none
 * returns:   int numItems from a node
 * effects:   none
 */
int CharLinkedList::size() const {
    return numItems;
}

/*
 * name:      isEmpty
 * purpose:   returns bool indicating whether CharLinkedList is empty
 * or not
 * arguments: none
 * returns:   bool value
 * effects:   none
 */
bool CharLinkedList::isEmpty() const {
    return (size() == 0);
}

/*
 * name:      first
 * purpose:   returns char from first node in linked list
 * arguments: none
 * returns:   char from a node
 * effects:   none
 */
char CharLinkedList::first() const {
    if (isEmpty()) {
        throw std::runtime_error("cannot get first of empty LinkedList");
    }
    return front->data;
}

/*
 * name:      last
 * purpose:   returns char from last node in linked list
 * arguments: none
 * returns:   char from a node
 * effects:   none
 */
char CharLinkedList::last() const {
    if (isEmpty()) {
        throw std::runtime_error("cannot get last of empty LinkedList");
    }
    return back->data;
}









