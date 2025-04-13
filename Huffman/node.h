//
// Created by Lucas on 4/12/2025.
//
#include "define.h"

#ifndef NODE_H
#define NODE_H


class Node {
public:
    Node* left;
    Node* right;
    uint8_t symbol;
    uint64_t frequency;

    // Constructor
    Node(uint8_t symbol, uint64_t frequency);

    // Destructor
    ~Node();

    // Check if this is a leaf node
    bool isLeaf() const;
};

// Function to join two nodes
Node* node_join(Node* left, Node* right);

#endif //NODE_H
