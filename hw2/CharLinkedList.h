/*
 *  CharLinkedList.h
 *  Jack Burton
 *  9/20/2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  CharLinkedList is a class that implements the list ADT by using nodes,
 *  each of which holds a char and points to the one before it and 
 *  after it in the linked list. These CharLinkedList instances will by 
 *  default be empty.
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <string>

class CharLinkedList {
public:
    // Constructors/Destructors
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);
    CharLinkedList &operator=(const CharLinkedList &other);
    ~CharLinkedList();

    // Implementation Functions
    bool isEmpty() const;
    int size() const;
    void insertAt(char c, int index);
    void pushAtFront(char c);
    void pushAtBack(char c);
    std::string toString() const;
    std::string toReverseString() const;
    void insertInOrder(char c);
    void popFromBack();
    void popFromFront();
    char elementAt(int index) const;
    void clear();
    void removeAt(int index);
    char first() const;
    char last() const;
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);


private:
    // Node struct is the core of the linked list. Each node points to the
    // one before it and the one after it.
    struct Node {
        char data;
        Node *prev;
        Node *next;
    };

    int numItems;
    Node *front;
    Node *back;

    // Helper functions
    void recycleRecursive(Node *curr);
    void removeAtHelper(Node *curr);
    Node *elementFinder(int ind, Node *curr) const;
    Node *newNode(char newData, Node *prev, Node *next);
};

#endif
