// Author: Jack Burton, Maurice Jang
// Date: Nov 29, 2023
//
// CS 15 Project 4: Gerp
// Name: index.h
//
// Purpose: interface for index class that indexes that contents of a directory
// into a hash to be queried

#ifndef _INDEX_CLASS
#define _INDEX_CLASS

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"
#include <functional>
#include <string>
#include "hash.h"
#include <set>

class Index {
  public:
    // Constructors/Destructors
    Index(); 
    Index(std::string searchDirectory);
    ~Index();

    std::string searchTableWrapper(std::string &word, bool CaseSense);
  
  private:
    // 2D array to store each file instance and all of its contents by line
    std::vector<std::vector<std::string>> fileLines;
    // 1D array to store the full path of each file
    std::vector<std::string> filePaths;

    Hash hashTable; 

    void traverse(DirNode *root, std::string path); 
    void catalog(std::string &fileName);    
    void indexWords(std::string &unparsedFileLine); 
    
    // Helper functions
    std::string stripNonAlphaNum(std::string &input); 
    std::string stripLeading(std::string &input);
    std::string stripTrailing(std::string &input);
};

#endif