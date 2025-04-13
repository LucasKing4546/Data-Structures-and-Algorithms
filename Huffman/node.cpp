//
// Created by Lucas on 4/12/2025.
//

#include "node.h"

Node::Node(uint8_t symbol, uint64_t frequency) {
    this->symbol = symbol;
    this->frequency = frequency;
}
Node::~Node() {
    delete left;
    delete right;
}

bool Node::isLeaf() const {
    return left == nullptr && right == nullptr;
}

Node* node_join(Node *left, Node *right) {
    Node* parent = new Node('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}


