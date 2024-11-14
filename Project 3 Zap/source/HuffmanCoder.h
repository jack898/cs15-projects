/*
 *  HuffmanCoder.h
 *  Jack Burton
 *  11/11/2023
 *
 *  CS 15 Proj 3 Zap
 *
 *  Declares functions for the HuffmanCoder class, which handles
 *  encoding "zapping" and decoding "unzapping" of valid files.
 *
 */

#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <queue>
#include <utility>

class HuffmanCoder {
   public:
    ~HuffmanCoder(); 

    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

   private:
    // Encoding/decoding helper functions
    std::string serializeTree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserializeTree(const std::string &s);
    HuffmanTreeNode 
    *deserializeTreeHelper(const std::string &serialTree, int &index);
    void buildNodes(std::istream &text, int charFreqs[256]);
    HuffmanTreeNode *buildTree();
    void genCharCodes
    (HuffmanTreeNode *root, std::string str, std::string charCodes[256]);
    std::string encodeText(std::ifstream &instream, std::string charCodes[256]);
    void decodeHelper
    (HuffmanTreeNode *root, std::ofstream &outstream, std::string bitstring);
    
    // Generic file/memory helper functions
    void recycle(HuffmanTreeNode *root);
    template <typename streamtype>
    void openFile(streamtype &stream, std::string fileName);

    
    // Helper variables
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, 
    NodeComparator> charPQ;

    
};

#endif