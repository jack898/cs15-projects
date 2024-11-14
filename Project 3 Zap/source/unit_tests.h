/*
 *  unit_tests.h
 *  Jack Burton
 *  11/5/2023
 *
 *  CS 15 Proj 3 Zap
 *
 *  Uses Matt Russell's unit_test framework to test Zap.
 *
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>

#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

/*****************************************************************************
                           Phase One Tests  

NOTE: Phase one tests have been commented out since function usage has changed
for phase 2.

// count_freqs() TESTS
// Since count_freqs prints to stdout, and since the table is allowed to be 
// in any order, each of these tests was just manually checked to ensure all
// characters were counted and with correct frequencies.

// Ensures count_freqs works for a simple txt string with no whitespaces 
// or newlines
void one_string_count_freqs() {
    std::ifstream input;
    input.open("testSimpleStr.txt");
    count_freqs(input);
    input.close();
}

// Ensure count_freqs works for a txt doc with all nonprinting ascii chars
void nonprinting_count_freqs() {
    std::ifstream input;
    input.open("nonprinting.txt");
    count_freqs(input);
    input.close();
}

// Ensure count_freqs works for a txt with newlines and whitespaces
void newlines_spaces_count_freqs() {
    std::ifstream input;
    input.open("testNewlinesSpaces.txt");

    count_freqs(input);
    input.close();
}

// Ensure count_freqs works for a stringstream
void count_freqs_stringstream() {
    std::stringstream stream ("hi hi\nhi");
    count_freqs(stream);
}

// serialize_tree() TESTS

// Ensure serialize_tree works for the tree from figure 1 in reference doc
void figure_one_tree_serialization() {
    HuffmanTreeNode *tree = makeFigure1Tree('\0');
    std::string serializedTree = serialize_tree(tree);

    assert(serializedTree == "IIILaLbILeLfILcLd");

    recycle(tree);
}

// Ensure serialize tree works for a 1 leaf tree
void one_leaf_tree_serialization() {
    HuffmanTreeNode *tree = new HuffmanTreeNode('a', 1);
    std::string serializedTree = serialize_tree(tree);
    
    assert(serializedTree == "La");

    recycle(tree);
}

// deserialize_tree() TESTS

// Ensure deserialize tree works for figure 1 tree serialization
void figure_one_tree_deserialization() {
    const std::string serializedTree = "IIILaLbILeLfILcLd";

    HuffmanTreeNode *tree = deserialize_tree(serializedTree);
    HuffmanTreeNode *comparison = makeFigure1Tree('\0');
    
    assert(treeEquals(tree, comparison, false, true));

    recycle(tree);
    recycle(comparison);
}

// Ensure deserialize tree works for a one leaf tree
void one_leaf_tree_deserialization() {
    const std::string serializedTree = "La";

    HuffmanTreeNode *tree = deserialize_tree(serializedTree);
    HuffmanTreeNode *compareTree = new HuffmanTreeNode('a', 0);  

    assert(treeEquals(tree, compareTree, false, true));

    recycle(tree);
    recycle(compareTree);
}

*****************************************************************************/

/*****************************************************************************/
/*                            Phase 2 Tests                                  */
/*****************************************************************************/

// buildNodes() TESTS
// NOTE: These tests do not pass valgrind because they are testing 
// a specific helper function--when this function is used in the
// implementation, the memory is properly freed.

// Ensure buildNodes works for a simple txt document with no spaces/newlines
void buildNodes_simple_str() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testSimpleStr.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    assert(instance.charPQ.size() == 4); // ensure all chars captured in PQ
    for (int i = 0; i < 3; i++) { // delete 3 min frequency nodes
        instance.charPQ.pop();
    }

     // ensure 'a' is max frequency node
    char topChar = instance.charPQ.top()->get_val();
    int topFreq = instance.charPQ.top()->get_freq();
    assert(topChar == 'a');
    assert(topFreq == 3);
}

// Ensure buildNodes works for a txt with nonprinting ascii chars
void buildNodes_nonprinting() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("nonprinting.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    assert(instance.charPQ.size() == 33); // ensure all chars captured in PQ
}

// Ensure buildNodes works for a txt with newlines and whitespaces
void buildNodes_newlines_spaces() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testNewlinesSpaces.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    assert(instance.charPQ.size() == 4); // ensure all chars captured in PQ
    for (int i = 0; i < 3; i++) { // delete 3 min frequency nodes
        instance.charPQ.pop();
    }
    char topChar = instance.charPQ.top()->get_val();
    int topFreq = instance.charPQ.top()->get_freq();
    assert(topChar == '\n');
    assert(topFreq == 4);
}

// buildTree() TESTS
// Ensure buildTree() works for a simple txt document with no spaces/newlines
void buildTree_simple_str() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testSimpleStr.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();

    assert(root->get_val() == '\0');
    assert(root->get_freq() == 6);
    assert(root->get_left()->get_val() == 'a');
    assert(root->get_left()->get_freq() == 3);
    assert(root->get_right()->get_val() == '\0');
    assert(root->get_right()->get_freq() == 3);
}

// Ensure buildTree() works for a txt with nonprinting ascii chars
void buildTree_nonprinting() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("nonprinting.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *tree = instance.buildTree();
    assert(tree->get_val() == '\0');
    assert(tree->get_freq() == 33);
    assert(tree->get_left()->get_val() == '\0');
    assert(tree->get_left()->get_freq() == 16);
    assert(tree->get_right()->get_val() == '\0');
    assert(tree->get_right()->get_freq() == 17);

}

// Ensure buildTree() works for a txt with newlines and whitespaces
void buildTree_newlines_spaces() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testNewlinesSpaces.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();
    std::cerr << root->get_freq() << std::endl;
    printTree(root, '\0');
    assert(root->get_val() == '\0');
    assert(root->get_freq() == 11);
}


// openFile() TESTS

// Ensure openFile() properly opens valid input file without error
void openFile_simple_str() {
    HuffmanCoder instance;
    std::ifstream input;
    instance.openFile(input, "testSimpleStr.txt");
    input.close();
}

// Ensure openFile() throws error when given invalid input file
void openFile_invalid_input() {
    HuffmanCoder instance;
    std::ifstream input;
    std::string errMsg = "";
    try {
        instance.openFile(input, "invalid.txt");
    } catch (std::runtime_error &e) {
        errMsg = e.what();
    }

    assert(errMsg == "Unable to open file invalid.txt");
}

// genCharCodes() TESTS
// NOTE: Only edge case is one unique char document--if it works for a simple
// txt document with multiple unique chars, should work for a doc with
// any number of unique ASCII chars--also further verified when testing 
// full encoder() function with longer docs.

// Ensure genCharCodes() works for a simple txt document
void genCharCodes_simple_str() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testSimpleStr.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();
    std::string charCodes[256];
    instance.genCharCodes(root, "", charCodes);

    assert(charCodes[97] == "0");
    assert(charCodes[110] == "10");
    assert(charCodes[78] == "110");
    assert(charCodes[98] == "111");
}

// Ensure genCharCodes() works for a one char txt document
void genCharCodes_onechar() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("onechar.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();
    std::string charCodes[256];
    instance.genCharCodes(root, "", charCodes);

    assert(charCodes[97] == "0");
}

// encodeText() TESTS

// Ensure that encodeText works for a one character txt doc
void encodeText_one_char() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("onechar.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();
    std::string charCodes[256];
    instance.genCharCodes(root, "", charCodes);

    std::ifstream input2;
    input2.open("onechar.txt");
    std::string encodedText = instance.encodeText(input2, charCodes);
    input2.close();


    assert(encodedText == "0");

}

// Ensure that encodeText works for a simple str txt doc
void encodeText_simple_str() {
    HuffmanCoder instance;
    std::ifstream input;
    input.open("testSimpleStr.txt");
    int charFreqs[256] = {0};
    instance.buildNodes(input, charFreqs);
    input.close();

    HuffmanTreeNode *root = instance.buildTree();
    std::string charCodes[256];
    instance.genCharCodes(root, "", charCodes);


    std::ifstream input2;
    input2.open("testSimpleStr.txt");
    std::string encodedText = instance.encodeText(input2, charCodes);
    input2.close();

    assert(encodedText == "11101100100");
}


// encoder() TESTS
// NOTE: Most tests for the full encoder() function involved zapping a file,
// comparing its memory to a memory of the same file zapped by the_zap, and then
// also unzapping that file with the_zap and diffing that with the original.

// Ensure encoder() does not throw any errors for a simple txt document
void encoder_simple_str() {
    HuffmanCoder instance;
    instance.encoder("testSimpleStr.txt", "testSimpleStr.zap");
}

// Ensure encoder() returns the error message when empty file is zapped
// (Manually check stdout for msg)
void encoder_empty_file() {
    HuffmanCoder instance;
    instance.encoder("emptyFile.txt", "empty.zap");
}

// decodeHelper() TESTS

// Ensure decodeHelper() throws runtime error with proper msg when given
// nonmatching huffman tree/bitstring
void decodeHelper_nonmatching_tree() {
    HuffmanCoder instance;
    std::string errMsg = "";
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    std::string bitstring = "00101";

    std::ofstream outstream;
    outstream.open("nonmatching.output");

    try {
        instance.decodeHelper(root, outstream, bitstring);  
    }
    catch (std::runtime_error &e) {
        errMsg = e.what();
    }
    outstream.close();
    instance.recycle(root);
    assert(errMsg == "Encoding did not match Huffman tree.");
}

// decoder() TESTS
// NOTE: Similar to encoder(), this was primarily tested by zapping files with
// the_zap and then unzapping then with zap and diffing that decoded version
// with the original.

// Ensure decoder() throws no errors when unzapping a valid simple str file
void decoder_simple_strs() {
    HuffmanCoder instance;
    instance.decoder("testSimpleStr.zap", "testSimpleStr.unzap");
}