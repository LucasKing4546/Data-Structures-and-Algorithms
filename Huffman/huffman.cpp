//
// Created by Lucas on 4/13/2025.
//


#include "huffman.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

// Custom comparator for the priority queue
struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

Huffman::Huffman() {
    treeSize = 0;
}

uint32_t Huffman::getTreeSize() const {
    return treeSize;
}


Node* Huffman::buildTree(uint64_t histogram[]) {
    // Create a priority queue of nodes
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;

    for (int i = 0; i < ALPHABET; i++) {
        if (histogram[i] > 0) {
            pq.push(new Node(i, histogram[i]));
            treeSize++;
        }
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = node_join(left, right);
        pq.push(parent);
    }

    return pq.empty() ? nullptr : pq.top();
}

void Huffman::buildCodeTable(Node* root, Code codeTable[]) {
    if (root == nullptr) return;
    Code code;
    buildCodeTableHelper(root, code, codeTable);
}

void Huffman::buildCodeTableHelper(Node* node, Code code, Code codeTable[]) {
    if (node == nullptr) return;

    if (node->isLeaf()) {
        codeTable[node->symbol] = code;
        return;
    }

    // Traverse left (add 0)
    Code leftCode = code;
    leftCode.push(0);
    buildCodeTableHelper(node->left, leftCode, codeTable);

    // Traverse right (add 1)
    Code rightCode = code;
    rightCode.push(1);
    buildCodeTableHelper(node->right, rightCode, codeTable);
}

Node* Huffman::reconstructTree(uint8_t treeData[], uint32_t treeSize) {
    std::stack<Node*> nodeStack;

    for (uint32_t i = 0; i < treeSize; i++) {
        if (treeData[i] == 'L') {
            // Next byte is the symbol
            i++;
            if (i < treeSize) {
                Node* leaf = new Node(treeData[i], 0); // Frequency doesn't matter for decoding
                nodeStack.push(leaf);
            }
        }
        else if (treeData[i] == 'I') {
            if (nodeStack.size() >= 2) {
                // Pop right child first, then left child
                Node* right = nodeStack.top();
                nodeStack.pop();

                Node* left = nodeStack.top();
                nodeStack.pop();

                // Join them and push parent back onto stack
                Node* parent = node_join(left, right);
                nodeStack.push(parent);
            }
        }
    }

    return nodeStack.empty() ? nullptr : nodeStack.top();
}