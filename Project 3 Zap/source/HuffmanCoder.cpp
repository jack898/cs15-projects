/*
 *  HuffmanCoder.cpp
 *  Jack Burton
 *  11/11/2023
 *
 *  CS 15 Proj 3 Zap
 *
 *  Contains the HuffmanCoder class function definitions.
 *
 */

#include "HuffmanCoder.h"
#include <string>

using namespace std;

/*
 * name:      destructor
 * purpose:   deletes all nodes in the char priority queue
 * arguments: none
 * returns:   none
 * effects:   char priority queue
 */
HuffmanCoder::~HuffmanCoder() {
    while (not charPQ.empty()) {
        recycle(charPQ.top());
        charPQ.pop();
    }
}

/*
 * name:      encoder
 * purpose:   compresses given inputFile and places compressed version into 
 * outputFile
 * arguments: reference to a string for an input file and reference to a string
 * for an output file
 * returns:   none
 * effects:   char priority queue, indirectly via buildTree function
 */
void HuffmanCoder::encoder(const string &inputFile, const string &outputFile) {
    ifstream instream;
    int charFreqs[256] = {0}; // array to store character frequencies
    string charCodes[256] = {""}; // array to store character codes
    string codeHolder; // placeholder for code of a particular character

    openFile(instream, inputFile);
    if (instream.peek() == ifstream::traits_type::eof()) {
        cout << inputFile << " is empty and cannot be compressed.\n";
        return;
    }
    /* Build huffman tree nodes, placing them into charPQ priority queue,
    and store each istream character's frequency in charFreqs array */
    buildNodes(instream, charFreqs);
    instream.close();

    openFile(instream, inputFile); // Re-open input stream from beginning
    HuffmanTreeNode *root = buildTree(); // Build Huffman Tree from charPQ nodes
    genCharCodes(root, codeHolder, charCodes); // Generate char codes from tree

    string bitstring = encodeText(instream, charCodes); // Encode given text
    string serialized_tree = serializeTree(root); // Serialize huffman tree
    BinaryIO binaryTools; 
    binaryTools.writeFile(outputFile, serialized_tree, bitstring);
    cout // Print success message if made it here without exception
    << "Success! Encoded given text using " << bitstring.length() << " bits.\n";

    instream.close();
}

/*
 * name:      decoder
 * purpose:   decompresses given binary zap file, or throws error if invalid
 * file. Places decompressed version into outputFile
 * arguments: reference to a string for an input file and reference to a string
 * for an output file
 * returns:   none
 * effects:   none
 */
void HuffmanCoder::decoder(const string &inputFile, const string &outputFile) {
    BinaryIO binaryTools; // read in binary and bitstring from inputFile
    pair<string, string> fileContents = binaryTools.readFile(inputFile);

    ofstream outstream; // open outstream to write decompressed text to
    openFile(outstream, outputFile);

    // deserialize the serialized tree string from fileContents.first
    HuffmanTreeNode *root = deserializeTree(fileContents.first);
    
    // decode the bitstring from fileContents.second using above tree
    decodeHelper(root, outstream, fileContents.second);

    recycle(root); // clear heap memory
    outstream.close();
}

/*
 * name:      decodeHelper
 * purpose:   Decodes bitstring using given huffman 
 * tree and writes to outstream
 * arguments: pointer to the root of a huffman tree, reference to an output
 * stream, and a string containing a bitstring
 * returns:   none
 * effects:   none
 */
void HuffmanCoder::decodeHelper
(HuffmanTreeNode *root, ofstream &outstream, string bitstring) {
    HuffmanTreeNode *curr = root;
    if (curr->isLeaf()) { // edge case for one unique character
        for (int i = 0; i < int(bitstring.length()); i++) {
            outstream << curr->get_val();
        }
        return;
    }
    for (char c : bitstring) { // iterate through each char in bitstring
        if (c == '1') {
            curr = curr->get_right();
        }
        else if (c == '0') {
            curr = curr->get_left();
        }
        if (curr->isLeaf()) { // add char to output file and return to root
            outstream << curr->get_val();
            curr = root;
        }
    } 
    if (curr != root) { // if curr is not root, then tree doesn't match
        throw runtime_error("Encoding did not match Huffman tree.");
    }
}

/*
 * name:      openFile
 * purpose:   generic filestream opening function
 * arguments: reference to a stream type and a string for the file name
 * returns:   none
 * effects:   none
 */
template <typename streamtype>
void HuffmanCoder::openFile(streamtype &stream, string fileName) {
        stream.open(fileName);
        if (not stream.is_open()) {
                throw runtime_error("Unable to open file " + fileName);
        }
}

/*
 * name:      buildNodes
 * purpose:   counts frequency of each character from input stream and
 * creates huffman nodes for them, pushing nodes onto the priority queue
 * arguments: a reference to an input stream, an array representing all possible
 * ascii chars
 * returns:   none
 * effects:   char priority queue 'charPQ'
 */
void HuffmanCoder::buildNodes(std::istream &text, int charFreqs[256]) {
    char c;
    while (text.get(c)) { // count frequency of each character in text istream
        charFreqs[(int)c]++;
    }

    for (int i = 0; i < 256; i++) { // build huffman nodes for each char
        if (charFreqs[i] > 0) { 
            HuffmanTreeNode *newNode = 
            new HuffmanTreeNode(char(i), charFreqs[i]);
            charPQ.push(newNode); // push nodes onto priority queue
        }
    }
}

/*
 * name:     serializeTree
 * purpose:  serializes a Huffman tree into a string
 * arguments: a pointer to the root of a Huffman tree
 * returns:  a string
 * effects:  none
 */
string HuffmanCoder::serializeTree(HuffmanTreeNode *root) {
    if (root->isLeaf()) {
            string leafInfo = "L";
            leafInfo += root->get_val(); // append leaf character
            return leafInfo;
    }
    
    else { // recursively append left and right subtree characters
        string internalNode = "I";
        internalNode += serializeTree(root->get_left());
        internalNode += serializeTree(root->get_right());
        return internalNode; 
    }
}


/*
 * name:     deserializeTree
 * purpose:  calls helper to deserialize huffman tree
 * arguments: a reference to a string
 * returns:  a pointer to the root of a Huffman tree
 * effects:  none
 */
HuffmanTreeNode *HuffmanCoder::deserializeTree(const string &serialTree) {
    // call helper starting at index 0 (root)
    int index = 0;
    return deserializeTreeHelper(serialTree, index);
}

/*
 * name:     deserializeTreeHelper
 * purpose:  deserializes serialized huffman tree string
 * arguments: a reference to a string, int with an index
 * returns:  a pointer to the root of a Huffman tree
 * effects:  none
 */
HuffmanTreeNode *HuffmanCoder::deserializeTreeHelper(const string &tree, 
int &index) {
    if (tree[index] == 'I') {
        HuffmanTreeNode *internal = new HuffmanTreeNode('\0', 0);
        ++index;
        internal->set_left(deserializeTreeHelper(tree, index));
        ++index;
        internal->set_right(deserializeTreeHelper(tree, index));
        return internal;
    }
    else { // node must be a leaf
        index++;
        char current = tree[index]; // capture node's character
        HuffmanTreeNode *leaf = new HuffmanTreeNode(current, 0);
        return leaf;
    } 
}

/*
 * name:     recycle
 * purpose:  uses post-order traversal to delete tree and recycle memory
 * arguments: a pointer to a huffman tree root
 * returns:  none
 * effects:  passed in huffman tree
 */
void HuffmanCoder::recycle(HuffmanTreeNode *root) {
    if (root == nullptr) { // base case empty tree
        return;
    }
    else { // recycle left, right, then root
        recycle(root->get_left());
        recycle(root->get_right());
        delete root;
    }
}

/*
 * name:     buildTree
 * purpose:  builds huffman tree from provided character frequency array
 * arguments: an array with ascii character frequencies
 * returns:  pointer to root of huffman tree 
 * effects:  priority queue
 */
HuffmanTreeNode *HuffmanCoder::buildTree() {
    while(charPQ.size() != 1) {  // exit loop once PQ only contains the root
        // create children nodes from min frequency nodes on PQ
        HuffmanTreeNode *leftChild = charPQ.top();
        charPQ.pop();
        HuffmanTreeNode *rightChild = charPQ.top();
        charPQ.pop();

        // create internal node w/ sum of children node frequencies
        HuffmanTreeNode *parentNode = new 
        HuffmanTreeNode('\0', leftChild->get_freq() + rightChild->get_freq());
        parentNode->set_left(leftChild);
        parentNode->set_right(rightChild);
        // push internal node onto PQ in place of children
        charPQ.push(parentNode);

    }

    return charPQ.top(); // return root of the tree
}


/*
 * name:     genCharCodes
 * purpose:  generates huffman character codes based on provided tree
 * arguments: pointer to root of a huffman tree, a placeholder string for a
 * character's code, and an array of all character codes
 * returns:  none
 * effects:  none
 */
void HuffmanCoder::genCharCodes
(HuffmanTreeNode *root, string code, string charCodes[256]) {
    if (root == nullptr) { // base case if reached end of tree
        return;
    }
    if (root->isLeaf() and code == "") { // edge case if one-char tree
        charCodes[int(root->get_val())] = "0";
        return;
    }
    // base case if leaf node, add respective code to charCodes array at proper
    // index for char
    if (root->isLeaf()) { 
        charCodes[int(root->get_val())] = code;
    }

    // Otherwise, recursively traverse tree to generate code
    genCharCodes(root->get_left(), code + "0", charCodes);
    genCharCodes(root->get_right(), code + "1", charCodes);
}

/*
 * name:     encodeText
 * purpose:  encodes text from input stream using provided character codes
 * arguments: reference to an input stream, an array of character codes
 * returns:  string containing encoded bitstring of text
 * effects:  none
 */
std::string HuffmanCoder::encodeText(ifstream &instream, string charCodes[256]) 
{
    string bitstring;
    char c;
    // Append code for each char from input stream to the bitstring
    while (instream.get(c)) {
        bitstring += charCodes[int(c)];
    }

    return bitstring;
}
