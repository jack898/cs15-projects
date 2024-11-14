// Author: Jack Burton, Maurice Jang
// Date: Dec 10, 2023
//
// CS 15 Project 4: Gerp
// Name: query.h
//
// Purpose: interface for a query class that will search a file directory
// based on user queries.

#include "index.h"


class Query {
    public: 
        void queryLoop(std::string &searchDir, std::ofstream &outstream);
    private:
}; 