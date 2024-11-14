// Author: Jack Burton, Maurice Jang
// Date: Nov 29, 2023
//
// CS 15 Project 4: Gerp
// Name: hash.cpp
//
// Purpose: implementation of the hash class functions

#include "hash.h"

using namespace std;

// Name: Hash
// Purpose: construct an empty hash table
// Input: none
// Ouput: none
// Effects: hashTable indirectly (via expand function call)
Hash::Hash() {
    currentTableSize = 10000;
    numItemsInTable = 0; 

    vector<list<wordInstance>> newHashTable(10000);
    hashTable = newHashTable;
}

// Name: insertHashWrapper
// Purpose: public wrapper for insertHash function
// Input: reference to a word string, reference to a vector of the line numbers,
// and reference to a vector of the file path indices.
// Output: nothing
// Effects: indirectly hash table via insertHash function
void Hash::insertHashWrapper(string &word, vector<int> &lineNumber, 
vector<int> &filePathIndex) {
    insertHash(hashTable, word, lineNumber, filePathIndex);
}


// Name: searchTable
// Purpose: search the hash table for a specific word
// Input: reference to a string, bool to determine if search is case sensitive, 
// wordInstance &wordInst 
// Ouput: nothing
// Effects: nothing
void Hash::searchTable(string &word, bool CaseSense, wordInstance &wordInst) {
    int bucket = wordHasher(word);  
    // Loop through the bucket corresponding to the word
    for (list<wordInstance>::iterator it = hashTable[bucket].begin();
        it != hashTable[bucket].end(); it++) {
        if (not CaseSense) { // find instances of ALL possible cases of a word
            if (compareCaseInsensitive(it->word, word)) {

                wordInst.lineNumbers.insert(wordInst.lineNumbers.end(), 
                it->lineNumbers.begin(), it->lineNumbers.end());

                wordInst.filePathIndexes.insert(wordInst.filePathIndexes.end(), 
                it->filePathIndexes.begin(), it->filePathIndexes.end());
            }
        } else { // only find instance of the specific case of the word
            if (it->word == word) 
                wordInst = *it;
        }
    }
}

// Name: wordHasher
// Purpose: hash and compress a lowercase version of the word
// Input: reference to a string
// Output: int representing the hash
// Effects: nothing
int Hash::wordHasher(string &word) {
    string lowerWord = word; 
    for (int i = 0; i < int(word.length()); i++) {
        lowerWord[i] = char(tolower(word[i]));
    }

    static hash<string> hashIndex; 
    return hashIndex(lowerWord) % currentTableSize;
}

// Name: compareCaseInsensitive
// Purpose: lower the letters of a word
// Input: string word1, word2
// Output: bool whether they are equal 
// Effects: nothing
bool Hash::compareCaseInsensitive(string &word1, string &word2) {
    if (word1.length() != word2.length())
        return false; 

    for (int i = 0; i < int(word1.length()); i++)
        if (char(tolower(word1[i])) != char(tolower(word2[i])))
            return false; 

    return true; 
}

// Name: expand
// Purpose: expand the hash table, rehashing all elements
// Input: desired new table size
// Output: nothing
// Effects: hash table size
void Hash::expand() {
    numItemsInTable = 0; // rehashing will update to proper size
    int oldTableSize = currentTableSize;
    currentTableSize = 2 * currentTableSize; // update table size
    vector<list<wordInstance>> newHashTable(currentTableSize);
    
    // Rehash all elements
    for (int i = 0; i < oldTableSize; i++) {
        for (list<wordInstance>::iterator it = hashTable[i].begin(); 
         it != hashTable[i].end(); it++) {
            insertHash(newHashTable, it->word, it->lineNumbers, 
            it->filePathIndexes);
         }
    }

    // Clear old table memory and change old table to the new expanded table
    hashTable.clear(); 
    hashTable = newHashTable;  
}


// Name: insertHash
// Purpose: insert the hashed string into the correct bucket, and expand 
// hash table if load factor is exceeded
// Input: reference to the hash table, reference to a word string, reference
// to a vector of the line numbers of that word, and reference to a vector of
// the file path indices of that word
// Output: nothing
// Effects: hash table indirectly via insertBucket function
void Hash::insertHash(vector<list<wordInstance>> &HT, string &word, 
vector<int> &lineNumber, vector<int> &filePathIndex)  {
    int index = wordHasher(word); 
    insertBucket(HT[index], word, lineNumber, filePathIndex); 

    if (numItemsInTable / currentTableSize >= 0.7)
        expand();
}

// Name: insertBucket
// Purpose: insert the word instance into a bucket
// Input: list bucket, wordInstance &wordInst
// Output: nothing
// Effects: nothing
void Hash::insertBucket(list<wordInstance> &bucket, string &word, 
vector<int> &lineNumber, vector<int> &filePathIndex) {
    for (list<wordInstance>::iterator it = bucket.begin(); 
         it != bucket.end(); it++) {
        if (it->word == word) {
            if (it->lineNumbers.back() == lineNumber.back() and
                it->filePathIndexes.back() == filePathIndex.back())
                return; 

            // add data of new occurence of an already seen word
            it->lineNumbers.push_back(lineNumber.back());
            it->filePathIndexes.push_back(filePathIndex.back());
            return;
        }
    }

    wordInstance newWord;
    newWord.word = word;
    newWord.lineNumbers = lineNumber; 
    newWord.filePathIndexes = filePathIndex; 
    bucket.push_back(newWord);
    
    numItemsInTable++;
}
