// Author: Maurice Jang and Jack Burton
// Data: November 29, 2023
//
// CS 15 Project 4: Gerp
//
// Purpose: test individual functions for the gerp project

#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
#include "index.h"


using namespace std;

/*****************************************************************************/
/* PHASE ONE TESTS                                                           */
/*****************************************************************************/
/*
// stringProcessing.cpp TESTS

// Ensure stripNonAlphaNum() properly removes leading and trailing 
// nonalphanum characters
void removeLeadingTrailing() {
    string test = "!@#$%^&*()_+1234abcd!@#$%^&*()_+";
    string expected = "1234abcd";
    string actual = stripNonAlphaNum(test);
    cerr << actual;
    assert(expected == actual);
}

// Ensure stripNonAlphaNum() properly keeps nonalphanumeric chars in the
// middle of the string
void keepMiddleNonAlphaNumChars() {
    string test = "1234!@#$%^&-abcd";
    string actual = stripNonAlphaNum(test);
    assert(actual == test); // No chars should be stripped from original
}

// Ensure stripNonAlphaNUm() properly keeps nonalphanum chars in the middle
// but removes leading/trailing nonalphanumeric chars
void keepMiddleRemoveLeadingTrailing() {
    string test = "@!##!!#!@!#COMP-15!!!!!!";
    string expected = "COMP-15";
    string actual = stripNonAlphaNum(test);
    assert(expected == actual);
}

// Ensure stripNonAlphaNum() properly removes all nonalphanumeric chars from
// a string with only nonalphanumeric
void removeAllNonAlphaNum() {
    string test = "!@#$%^&*()_+";
    string actual = stripNonAlphaNum(test);
    assert(actual == "");
}

// Ensure  that stripNonAlphaNum() does not strip real words
void donotRemoveWord(){
    string test = "1234abcd";
    string actual = stripNonAlphaNum(test);
    assert(test == actual); 
}

// Ensure  that stripNonAlphaNum() can handle an empty string
void emptyString(){
    string actual = stripNonAlphaNum("");
    assert(actual == "");
}

// NOTE: Phase 1's 
// FSTreeTraversal.cpp was tested manually using TestDir, a test directory
// containing subdirectories and files.
*/

/*****************************************************************************/
/* PHASE TWO TESTS                                                           */
/*****************************************************************************/
//INDEX CLASS TESTS

//Index Constructor tests

// Ensure that index constructor properly initializes an index using a test
// directory
void indexConstructor() {
    Index test("testDir");

    // Check that all file paths are stored properly
    string path1 = test.filePaths[0];
    string path2 = test.filePaths[1];
    string path3 = test.filePaths[2];
    string path4 = test.filePaths[3];
    string path5 = test.filePaths[4];
    assert(path1 == "testDir/test2.txt");
    assert(path2 == "testDir/test1.txt");
    assert(path3 == "testDir/testSubDir/testSub1.txt");
    assert(path4 == "testDir/testSubDir/testSub2.txt");
    assert(path5 == "testDir/testSubDir/testSubSubDir/testSubSub1.txt");
    
    // test2.txt contents
    assert(test.fileLines[0][0] == "rt");
    assert(test.fileLines[0][1] == "");
    assert(test.fileLines[0][2] == "asdf");

    // test1.txt contents
    assert(test.fileLines[1][0] == "tgty");
    assert(test.fileLines[0][1] == "");

    // testSub1.txt contents
    assert(test.fileLines[2][0] == "erg");
    assert(test.fileLines[2][1] == "argh");
    assert(test.fileLines[2][2] == "oogh");

    // testSub2.txt contents
    assert(test.fileLines[3][0] == "rt");

    // testSubSub1.txt contents
    assert(test.fileLines[4][0] == "fgb");
    
}


// Index Destructor tests

// Ensure that index destructor properly deallocates memory 
// (no valgrind errors)
void indexDestructor() {
    Index test("testDir");
}

// traverse() tests

// Ensure that traverse() properly traverses a directory and stores the
// file paths in the index
void traverse_test_dir() {
    Index test("testDir");
    
    string path1 = test.filePaths[0];
    string path2 = test.filePaths[1];
    string path3 = test.filePaths[2];
    string path4 = test.filePaths[3];
    string path5 = test.filePaths[4];
    assert(path1 == "testDir/test2.txt");
    assert(path2 == "testDir/test1.txt");
    assert(path3 == "testDir/testSubDir/testSub1.txt");
    assert(path4 == "testDir/testSubDir/testSub2.txt");
    assert(path5 == "testDir/testSubDir/testSubSubDir/testSubSub1.txt");
}

// catalog() tests

// Ensure that catalog() properly stores the contents of a testing file
void catalog_test_dir_test1() {
    Index test;
    
    string dir = "testDir/test1.txt"; 
    test.catalog(dir);
    string line1 = test.fileLines[0][0];
    string line2 = test.fileLines[0][1];

    assert(line1 == "tgty");
    assert(line2 == "");
}

// indexWords() tests

// Ensure that indexWords() properly indexes a line of text
void indexWordsOneLine() {
    Index test("testDir/testSubDir/testSubSubDir");
    Hash hasher = test.hashTable; 
    string word = "fgb";

    assert(hasher.searchTable(word, true) != nullptr);
    assert(hasher.searchTable(word, true)->word == word);
    assert(hasher.searchTable(word, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word, true)->filePathIndexes.front() == 0);
}


// Ensure that indexWords() properly indexes a file with an empty line
void testIndexEmptyLine() {
    
    Index test("newTestDir");
    Hash hasher = test.hashTable;
    string line1 = "line1";
    string line3 = "line3";

    // Ensure first line text is stored properly
    assert(hasher.searchTable(line1, true)->word == "line1");
    assert(hasher.searchTable(line1, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(line1, true)->filePathIndexes.front() == 0);

    // Ensure line three text is stored in proper location in hash
    assert(hasher.searchTable(line3, true)->word == "line3");
    assert(hasher.searchTable(line3, true)->lineNumbers.front() == 3);
    assert(hasher.searchTable(line3, true)->filePathIndexes.front() == 0);
}

// Ensure indexWords() properly indexes an entire subdirectory with multiple
// files
void testSubDirIndexing() { 
    Index test("testDir"); 
    Hash hasher = test.hashTable; 
    
    // test2.txt words and testSub2.txt word1
    string word1 = "rt";
    string word2 = "asdf";

    // test1.txt words
    string word3 = "tgty";
    
    // testSub1.txt words
    string word4 = "erg";
    string word5 = "argh";
    string word6 = "oogh";
    
    // testSub2.txt words
    // word1 "rt"

    // testSubSub1.txt word
    string word7 = "fgb";
    string word8 = "yyy"; 
    string word9 = "rrr"; 
    string word10 = "ggg"; 

    // test2.txt
    assert(hasher.searchTable(word1, true)->word == word1);
    assert(hasher.searchTable(word1, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word1, true)->lineNumbers.back() == 1);
    assert(hasher.searchTable(word1, true)->filePathIndexes.front() == 0);
    // filePathIndexes should also include 3 because word1 is also in file 4,
    // testSub2.txt
    assert(hasher.searchTable(word1, true)->filePathIndexes.back() == 3);

    assert(hasher.searchTable(word2, true)->word == word2);
    assert(hasher.searchTable(word2, true)->lineNumbers.front() == 3);
    assert(hasher.searchTable(word2, true)->filePathIndexes.front() == 0);
    

    // test1.txt 
    assert(hasher.searchTable(word3, true)->word == word3);
    assert(hasher.searchTable(word3, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word3, true)->filePathIndexes.front() == 1);

    // testSub1.txt 
    assert(hasher.searchTable(word4, true)->word == word4);
    assert(hasher.searchTable(word4, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word4, true)->filePathIndexes.front() == 2);
    
    assert(hasher.searchTable(word5, true)->word == word5);
    assert(hasher.searchTable(word5, true)->lineNumbers.front() == 2);
    assert(hasher.searchTable(word5, true)->filePathIndexes.front() == 2);
    
    assert(hasher.searchTable(word6, true)->word == word6);
    assert(hasher.searchTable(word6, true)->lineNumbers.front() == 3);
    assert(hasher.searchTable(word6, true)->filePathIndexes.front() == 2);

    
    // testSubSub1.txt 
    assert(hasher.searchTable(word7, true)->word == word7);
    assert(hasher.searchTable(word7, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word7, true)->filePathIndexes.front() == 4);

    assert(hasher.searchTable(word8, true)->word == word8);
    assert(hasher.searchTable(word8, true)->lineNumbers.front() == 1);
    assert(hasher.searchTable(word8, true)->filePathIndexes.front() == 4);

    assert(hasher.searchTable(word9, true)->word == word9);
    assert(hasher.searchTable(word9, true)->lineNumbers.front() == 2);
    assert(hasher.searchTable(word9, true)->filePathIndexes.front() == 4);

    assert(hasher.searchTable(word10, true)->word == word10);
    assert(hasher.searchTable(word10, true)->lineNumbers.front() == 2);
    assert(hasher.searchTable(word10, true)->filePathIndexes.front() == 4);

}




// QUERY CLASS TESTS
// The query class only has one function for the query loop, so we found it
// more intuitive to test this with diffing and just manually/visually.

// HASH CLASS TESTS

// Constructor tests

// Ensure that Hash constructor properly initializes a hash table
// (no errors)
void hashConstructor() {
    Hash test;
    assert(test.currentTableSize == 10000);
    assert(test.numItemsInTable == 0);
}

// insertBucket() tests

// Ensure that insertBucket properly inserts a wordInstance into a hashTable
void insertNewWordBucket() {
    Hash test;

    string word = "word";
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertBucket(test.hashTable[0], word, word1Line, word1Path);

    // Ensure number of items in table is updated properly
    assert(test.numItemsInTable == 1);
    assert(test.currentTableSize == 10000);

    // Ensure that word is stored in correct bucket and stored properly
    assert(test.hashTable[0].size() == 1); 
    assert(test.hashTable[0].back().word == "word");
    assert(test.hashTable[0].back().lineNumbers.back() == 1);
    assert(test.hashTable[0].back().filePathIndexes.back() == 1);
}

// Ensure that insertBucket properly inserts a new instance of a word that 
// we have already indexed
void insertWordTwice() {
    Hash test;

    string word1 = "word";
    string word2 = "word";
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertBucket(test.hashTable[0], word1, word1Line, word1Path);
    test.insertBucket(test.hashTable[0], word2, word2Line, word2Path);

    assert(test.numItemsInTable == 1);
    assert(test.currentTableSize == 10000);

    // Ensure that each word instance is stored properly in the same node
    assert(test.hashTable[0].size() == 1); 
    assert(test.hashTable[0].back().word == "word");
    assert(test.hashTable[0].back().lineNumbers.front() == 1);
    assert(test.hashTable[0].back().filePathIndexes.front() == 1);
    assert(test.hashTable[0].back().lineNumbers.back() == 2);
    assert(test.hashTable[0].back().filePathIndexes.back() == 3);

}

// Ensure that insertBucket properly inserts two different words
void insertTwoWords() {
    Hash test;

    string word1 = "word";
    string word2 = "Word";
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertBucket(test.hashTable[0], word1, word1Line, word1Path);
    test.insertBucket(test.hashTable[0], word2, word2Line, word2Path);

    assert(test.numItemsInTable == 2);
    assert(test.currentTableSize == 10000);

    // Ensure that each word instance is stored properly in the same node
    assert(test.hashTable[0].size() == 2); 
    assert(test.hashTable[0].front().word == "word");
    assert(test.hashTable[0].back().word == "Word");
    assert(test.hashTable[0].front().lineNumbers.front() == 1);
    assert(test.hashTable[0].front().filePathIndexes.front() == 1);
    assert(test.hashTable[0].back().lineNumbers.front() == 2);
    assert(test.hashTable[0].back().filePathIndexes.front() == 3);
}

// wordHasher() tests

// Ensure that wordHasher() properly hashes a string (no errors and returns
// an index that is within currentTableSize of 10000)
void hashString() {
    Hash test;
    string toHash = "test";

    int hashIndex = test.wordHasher(toHash);

    assert(hashIndex < 10000);
}


// insertHash() tests

// Ensure insertHash() properly inserts a wordInstance into the hash table
void insertOneHashedWord() {
    Hash test;

    string word = "word";
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertHash(test.hashTable, word, word1Line, word1Path);

    assert(test.numItemsInTable == 1);
    assert(test.currentTableSize == 10000);


    assert(test.hashTable[hashIndex].size() == 1); 
    assert(test.hashTable[hashIndex].back().word == "word");
    assert(test.hashTable[hashIndex].back().lineNumbers.front() == 1);
    assert(test.hashTable[hashIndex].back().filePathIndexes.front() == 1);
}

// Ensure that insertHash properly inserts a new instance of a word that 
// we have already indexed
void insertOneHashedWordTwice() {
    Hash test;

    string word = "word";
  
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertHash(test.hashTable, word, word1Line, word1Path);
    test.insertHash(test.hashTable, word, word2Line, word2Path);
    assert(test.numItemsInTable == 1);
    assert(test.currentTableSize == 10000);

    // Ensure that each word instance is stored properly in the same node
    assert(test.hashTable[hashIndex].size() == 1); 
    assert(test.hashTable[hashIndex].back().word == "word");
    assert(test.hashTable[hashIndex].back().lineNumbers.front() == 1);
    assert(test.hashTable[hashIndex].back().filePathIndexes.front() == 1);
    assert(test.hashTable[hashIndex].back().lineNumbers.back() == 2);
    assert(test.hashTable[hashIndex].back().filePathIndexes.back() == 3);

}

// Ensure that insertHash properly inserts a new instance of a word that 
// we have already indexed
void insertTwoHashedWordTwice() {
    Hash test;

    string word1 = "word";
    string word2 = "Word";
  
    int hashIndex = test.wordHasher(word1);
    assert(hashIndex == test.wordHasher(word2)); 
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertHash(test.hashTable, word1, word1Line, word1Path);
    test.insertHash(test.hashTable, word2, word2Line, word2Path);
    assert(test.numItemsInTable == 2);
    assert(test.currentTableSize == 10000);

    // Ensure that each word instance is stored properly in the same node
    assert(test.hashTable[hashIndex].size() == 2); 
    assert(test.hashTable[hashIndex].front().word == "word");
    assert(test.hashTable[hashIndex].back().word == "Word");
    assert(test.hashTable[hashIndex].front().lineNumbers.front() == 1);
    assert(test.hashTable[hashIndex].front().filePathIndexes.front() == 1);
    assert(test.hashTable[hashIndex].back().lineNumbers.front() == 2);
    assert(test.hashTable[hashIndex].back().filePathIndexes.front() == 3);
}

// Ensure that insertHash properly inserts two entirely different strings
void insertTwoDifferentWordsHashed() {
    Hash test;

    string word1 = "word";
    string word2 = "apple";

  
    int hashIndex1 = test.wordHasher(word1);
    int hashIndex2 = test.wordHasher(word2);

    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertHash(test.hashTable, word1, word1Line, word1Path);
    test.insertHash(test.hashTable, word2, word2Line, word2Path);
    assert(test.numItemsInTable == 2);
    assert(test.currentTableSize == 10000);

    // Ensure that each word instance is stored properly in different buckets
    assert(test.hashTable[hashIndex1].size() == 1); 
    assert(test.hashTable[hashIndex2].size() == 1); 
    assert(test.hashTable[hashIndex1].front().word == "word");
    assert(test.hashTable[hashIndex2].back().word == "apple");
    assert(test.hashTable[hashIndex1].front().lineNumbers.front() == 1);
    assert(test.hashTable[hashIndex1].front().filePathIndexes.front() == 1);
    assert(test.hashTable[hashIndex2].back().lineNumbers.front() == 2);
    assert(test.hashTable[hashIndex2].back().filePathIndexes.front() == 3);
}

// Ensure that insertHash() can insert 10000 elements into the hash table
// (Also makes sure expand() and searchTable() work properly)
void insert10000HashedWords() {
    Hash test;

    for (int i = 0; i < 10000; i++) {
        string word = to_string(i);
        int hashIndex = test.wordHasher(word);
        vector<int> word1Line(1, 1);
        vector<int> word1Path(1, 1);
        test.insertHash(test.hashTable, word, word1Line, word1Path);
    }

    assert(test.numItemsInTable == 10000);
    // Ensure hash table expanded properly
    assert(test.currentTableSize == 20000);
    // Ensure that each word instance is stored properly in different buckets
    for (int i = 0; i < 10000; i++) {
        string word = to_string(i);
        Hash::wordInstance *wordInst = test.searchTable(word, true); \
        assert(wordInst->word == word); 
        assert(wordInst->lineNumbers.front() == 1); 
        assert(wordInst->filePathIndexes.front() == 1); 
    }
}

// expand() tests

// Ensure that expansion works properly
void expand_table() {

    Hash test;

    string word1 = "word";
    string word2 = "apple";

  
    int hashIndex1 = test.wordHasher(word1);
    int hashIndex2 = test.wordHasher(word2);

    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    vector<int> word2Line(1, 2);
    vector<int> word2Path(1, 3);
    test.insertHash(test.hashTable, word1, word1Line, word1Path);
    test.insertHash(test.hashTable, word2, word2Line, word2Path);

    test.expand();

    hashIndex1 = test.wordHasher(word1);
    hashIndex2 = test.wordHasher(word2);
    cerr << test.numItemsInTable << endl;
    assert(test.numItemsInTable == 2);
    assert(test.currentTableSize == 20000);

    assert(test.hashTable[hashIndex1].size() == 1); 
    assert(test.hashTable[hashIndex2].size() == 1); 
    assert(test.hashTable[hashIndex1].front().word == "word");
    assert(test.hashTable[hashIndex2].back().word == "apple");
    assert(test.hashTable[hashIndex1].front().lineNumbers.front() == 1);
    assert(test.hashTable[hashIndex1].front().filePathIndexes.front() == 1);
    assert(test.hashTable[hashIndex2].back().lineNumbers.front() == 2);
    assert(test.hashTable[hashIndex2].back().filePathIndexes.front() == 3);

}

// searchTable() tests

// Ensure that searchTable() properly finds a word in the hash table
void searchTableExistingWord() {
    Hash test;

    string word = "word";
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertHash(test.hashTable, word, word1Line, word1Path);

    Hash::wordInstance* foundWord = test.searchTable(word, true);
    
    assert(foundWord->word == word);
    assert(foundWord->lineNumbers.front() == 1);
    assert(foundWord->filePathIndexes.front() == 1);

}

// Ensure that searchTable() properly returns a nullptr if the word is not
// found in the hash table
void searchTableNonexistantWord() {
    Hash test;

    string word = "word";
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertHash(test.hashTable, word, word1Line, word1Path);

    
    string word2 = "apple"; 
    Hash::wordInstance* foundWord = test.searchTable(word2, true);

    assert(foundWord == nullptr);
}


// Ensure that searchTable() properly finds a word in the hash table case
// insensitively
void searchTableExistingWordCaseInsensitively() {
    Hash test;

    string word = "word";
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertHash(test.hashTable, word, word1Line, word1Path);

    string WORD = "WORD";
    Hash::wordInstance* foundWord = test.searchTable(WORD, false);
    
    assert(foundWord->word == word);
    assert(foundWord->lineNumbers.front() == 1);
    assert(foundWord->filePathIndexes.front() == 1);

}

// Ensure that searchTable() properly finds a word in the hash table case
// insensitively
void searchTableNonExistingWordCaseSensitively() {
    Hash test;

    string word = "word";
    int hashIndex = test.wordHasher(word);
    vector<int> word1Line(1, 1);
    vector<int> word1Path(1, 1);
    test.insertHash(test.hashTable, word, word1Line, word1Path);

    string WORD = "WORD";
    Hash::wordInstance* foundWord = test.searchTable(WORD, true);
    
    assert(foundWord == nullptr);
}

// Testing tinyData with indexing
void sendHelp() {
    Index test("tinyData");
    string I = "I"; 

    Hash::wordInstance *wordInst = 
    test.hashTable.searchTable(I, true);

    cerr << test.fileLines.size() << endl;
    cerr << test.filePaths[6] << endl;
    cerr << test.fileLines[6].size() << endl;
    
}



