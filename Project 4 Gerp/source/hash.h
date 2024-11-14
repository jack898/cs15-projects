// Author: Jack Burton, Maurice Jang
// Date: Nov 29, 2023
//
// CS 15 Project 4: Gerp
// Name: hash.h
//
// Purpose: interface for a hash class that stores strings

#include <string>
#include <functional>
#include <vector>
#include <list>
#include <iostream>
#include <ctype.h>
#include <stdio.h>


class Hash {

  public:
    Hash();

    void insertHashWrapper(std::string &word, 
    std::vector<int> &lineNumber, std::vector<int> &filePathIndex);


  
    // Struct to store each instance of a word
    struct wordInstance {
        std::string word;
        // Vector to store line number of each instance of a word
        std::vector<int> lineNumbers; 
        // Vector to store index of the file path for each instance of a word
        std::vector<int> filePathIndexes;
    };

    void searchTable(std::string &word, bool CaseSense, wordInstance &wordInst);

  private:
    
    
    // Hash function and hash table
    // std::hash<std::string> hashFunction;
    std::vector<std::list<wordInstance>> hashTable;

    int currentTableSize;
    int numItemsInTable;

    int wordHasher(std::string &word);
    bool compareCaseInsensitive(std::string &word1, std::string &word2); 
    void expand();

    // Relies on private insertBucket helper function  
    void insertHash(std::vector<std::list<wordInstance>> &HT, 
    std::string &word, std::vector<int> &lineNumber, 
    std::vector<int> &filePathIndex);
    void insertBucket(std::list<wordInstance> &bucket, std::string &word, 
    std::vector<int> &lineNumber, std::vector<int> &filePathIndex);
};
