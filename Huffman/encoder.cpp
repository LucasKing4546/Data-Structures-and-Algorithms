//
// Created by Lucas on 4/13/2025.
//
#include <fstream>
#include <iostream>
#include <filesystem>
#include <getopt.h>
#include <vector>

#include "define.h"
#include "huffman.h"
#include "io.h"

void print_help() {
    std::cout << "SYNOPSIS\n"
              << "  A Huffman encoder.\n\n"
              << "USAGE\n"
              << "  ./encode [-h] [-i infile] [-o outfile] [-s]\n\n"
              << "OPTIONS\n"
              << "  -h             Program help and usage.\n"
              << "  -i infile      Input file to encode.\n"
              << "  -o outfile     Output file for encoded data.\n"
              << "  -s             Print compression statistics.\n";
}

// Function to dump the Huffman tree in post-order traversal
void dumpTree(Node* root, std::vector<uint8_t> &tree_dump) {
    if (root == nullptr) return;

    // Post-order traversal: left, right, node
    dumpTree(root->left, tree_dump);
    dumpTree(root->right, tree_dump);

    // If leaf node, dump 'L' followed by symbol
    if (root->isLeaf()) {
        tree_dump.push_back('L');
        tree_dump.push_back(root->symbol);
    } else {
        // If interior node, just dump 'I'
        tree_dump.push_back('I');
    }
}

int main(int argc, char *argv[]) {
    // Default values
    std::string infile = "-";  // Default to stdin
    std::string outfile = "";  // Required
    bool print_stats = false;

    // Parse command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "hi:o:s")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'i':
                infile = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case 's':
                print_stats = true;
                break;
            default:
                print_help();
                return 1;
        }
    }

    // Check if output file was specified
    if (outfile.empty()) {
        std::cerr << "Output file must be specified." << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream input;
    if (infile != "-") {
        input.open(infile, std::ios::binary);
        if (!input.is_open()) {
            std::cerr << "Could not open input file: " << infile << std::endl;
            return 1;
        }
    }
    std::istream &in = (infile != "-") ? input : std::cin;

    // Calculate file size
    uint64_t file_size = 0;
    if (infile != "-") {
        file_size = std::filesystem::file_size(infile);
    } else {
        // For stdin, we'll count bytes as we read them
    }

    // Create histogram
    uint64_t histogram[ALPHABET] = {0};

    // Increment positions 0 and 255 as required
    histogram[0]++;
    histogram[255]++;

    // Read input file and build histogram
    uint8_t byte;
    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        histogram[byte]++;
        if (infile == "-") file_size++; // Count bytes for stdin
    }

    // Reset input file to beginning
    if (infile != "-") {
        input.clear();
        input.seekg(0);
    } else {
        // Can't reset stdin, need to handle differently
        std::cerr << "Cannot process stdin as input" << std::endl;
        return 1;
    }

    // Build Huffman tree and code table
    Huffman huffman;
    Node* root = huffman.buildTree(histogram);
    Code codeTable[ALPHABET];
    huffman.buildCodeTable(root, codeTable);

    // Create tree dump
    std::vector<uint8_t> tree_dump;
    dumpTree(root, tree_dump);

    // Create and write header
    Header header;
    header.magic = MAGIC;
    header.tree_size = tree_dump.size();
    header.file_size = file_size;

    // Open output file
    std::ofstream output(outfile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Could not open output file: " << outfile << std::endl;
        return 1;
    }

    // Write header
    output.write(reinterpret_cast<char*>(&header), sizeof(Header));

    // Write tree dump
    output.write(reinterpret_cast<char*>(tree_dump.data()), tree_dump.size());

    // Create bit writer
    BitWriter writer(output);

    // Encode file
    while (input.read(reinterpret_cast<char*>(&byte), 1)) {
        Code code = codeTable[byte];
        for (int i = 0; i < code.size(); i++) {
            writer.writeBit(code.bits[i]);
        }
    }

    // Get compressed size
    uint64_t compressed_size = sizeof(Header) + tree_dump.size();
    if (print_stats) {
        double space_saving = 100.0 * (1.0 - (double)compressed_size / file_size);
        std::cerr << "Uncompressed file size: " << file_size << " bytes" << std::endl;
        std::cerr << "Compressed file size: " << compressed_size << " bytes" << std::endl;
        std::cerr << "Space saving: " << space_saving << "%" << std::endl;
    }

    return 0;
}