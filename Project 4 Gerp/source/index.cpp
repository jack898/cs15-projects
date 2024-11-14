// Author: Jack Burton, Maurice Jang
// Date: Dec 3, 2023
//
// CS 15 Project 4: Gerp
// File name: index.cpp
//
// Purpose: implentation of the index class functions

#include "index.h"


using namespace std;


Index::Index() {
}

// Name: Index
// Purpose: construct the index clas
// Input: name of the subdirectory
// Output: nothing
// Effects: nothing
Index::Index(string searchDir) {
   FSTree tree(searchDir);
   string empty = "";
   traverse(tree.getRoot(), empty); 

   tree.burnTree();
}



// Name: ~Index
// Purpose: recycle any heap memory
// Input: none
// Output: none
// Effects: the FSTree
Index::~Index() {
    
}

// Name: searchTableWrapper
// Purpose: wrapper to search the table for a stripped version of the word
// and with case sensitivity/insensitivity and return a properly formatted
// string for the results file.
// Input: reference to the word and a bool for case sensitivity
// Ouput: string containing properly formatted results for one word
// Effects: hash table indirectly
string Index::searchTableWrapper(string &word, bool CaseSense) {
    string strippedWord = stripNonAlphaNum(word);
    Hash::wordInstance wordInst;
    hashTable.searchTable(strippedWord, CaseSense, wordInst);
    stringstream output; 

    // If word not found OR invalid string (of only nonalphanum) was given
    if (wordInst.lineNumbers.empty() or strippedWord.empty()) {
        output << strippedWord << " Not Found."; 
        if (CaseSense)
           output << " Try with @insensitive or @i.";
        output << "\n";
        return output.str(); 
    } 
    set<string> wordData; 
    for (int i = 0; i < int(wordInst.lineNumbers.size()); i++) {
        wordData.insert(filePaths[wordInst.filePathIndexes[i]] + ":" 
        + to_string(wordInst.lineNumbers[i]) + ": " 
        + fileLines[wordInst.filePathIndexes[i]][wordInst.lineNumbers[i] - 1]
        + "\n");
    }
    set<string>::iterator it;
    for (it = wordData.begin(); it != wordData.end(); ++it)
        output << *it; 

    return output.str(); 
}



// Name: traverse
// Purpose: traverse through FS tree and print pathways to each file
// Input: DirNode *root, string path
// Ouput: nothing
// Effects: nothing
void Index::traverse(DirNode *root, string path) {

    path = path + root->getName() + "/"; 

    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            string fullPath = path + root->getFile(i);
            filePaths.push_back(fullPath);
            catalog(fullPath); 
        }
    }
    if (root->hasSubDir()) {
        for (int i = 0; i < root->numSubDirs(); i++) {
            traverse(root->getSubDir(i), path);
        }
    }
}

// Name: catalog
// Purpose: catalog each line and index each word
// Input: reference to string 
// Output: nothing
// Effects: fileLines vector
void Index::catalog(string &fileName) {
    ifstream inStream;
    inStream.open(fileName);

    string tempLineStorage; // string to store each line during getline

    fileLines.resize(fileLines.size() + 1); 
    while (getline(inStream, tempLineStorage)) {
        fileLines.back().push_back(tempLineStorage);
        indexWords(tempLineStorage);
    }
    

    inStream.close(); 
}

// Name: indexWords
// Purpose: record the words in a give line
// Input: string &unparsedFileLine
// Output: nothing
// Effects: nothing
void Index::indexWords(string &unparsedFileLine) {

    std::stringstream ss(unparsedFileLine); 

    string word; 
    vector<int> lineNumber(1, fileLines[fileLines.size() - 1].size()); 
    vector<int> filePathIndex(1, fileLines.size() - 1); 

    while(ss >> word) {
        word = stripNonAlphaNum(word);
        hashTable.insertHashWrapper(word, lineNumber, filePathIndex); 
    }

}

// Name: stringNonAlphaNum
// Purpose: strip string of non alphanumeric chars
// Input: string input which is to be parsed
// Output: the parsed string
// Effects: nothing
string Index::stripNonAlphaNum(string &input) {
    string leadingRemoved = stripLeading(input);
    return stripTrailing(leadingRemoved);
}

// Name: stripLeading
// Purpose: strip leading non alphanumeric chars
// Input: string input
// Ouput: string 
// Effects: nothing
string Index::stripLeading(string &input) {
    while ((not isalnum(input[0])) and (not input.empty())) 
        input.erase(0, 1);
    
    return input;
}

// Name: stripTrailing
// Purpose: strip trailing non alphanumeric chars
// Input: string input
// Ouput: string 
// Effects: nothing
string Index::stripTrailing(string &input) {
    while((not isalnum(input[input.length() - 1])) and (not input.empty()))
        input.erase(input.length() - 1, 1);

    return input; 
}




