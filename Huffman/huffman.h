//
// Created by Lucas on 4/12/2025.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <cstdint>
#include "define.h"
#include "node.h"
#include "code.h"

class Huffman {
public:
    // Constructor
    Huffman();

    uint32_t getTreeSize() const;
    
    // Construct a Huffman tree from a histogram of symbol frequencies
    Node* buildTree(uint64_t histogram[]);
    
    // Create a code table by traversing the Huffman tree
    void buildCodeTable(Node* root, Code codeTable[]);
    
    // Reconstruct a Huffman tree from its post-order traversal
    Node* reconstructTree(uint8_t treeData[], uint32_t treeSize);
    
private:
    uint32_t treeSize;
    void buildCodeTableHelper(Node* node, Code code, Code codeTable[]);
};

#endif //HUFFMAN_H