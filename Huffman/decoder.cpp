//
// Created by Lucas on 4/13/2025.
//
#include <fstream>
#include <iostream>
#include <filesystem>
#include <getopt.h>
#include <cstring>

#include "define.h"
#include "huffman.h"
#include "io.h"

void print_help() {
    std::cout << "  A Huffman decoder.\n\n"
              << "USAGE\n"
              << "  ./decode [-h] [-i infile] [-o outfile] [-s]\n\n"
              << "OPTIONS\n"
              << "  -h             Program help and usage.\n"
              << "  -i infile      Input file to decode.\n"
              << "  -o outfile     Output file for decoded data.\n"
              << "  -s             Print decompression statistics.\n";
}

int main(int argc, char *argv[]) {
    std::string infile = "";
    std::string outfile = "-"; // Default to stdout
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

    // Check if input file was specified
    if (infile.empty()) {
        std::cerr << "Input file must be specified." << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream input(infile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Could not open input file: " << infile << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream output;
    if (outfile != "-") {
        output.open(outfile, std::ios::binary);
        if (!output.is_open()) {
            std::cerr << "Could not open output file: " << outfile << std::endl;
            return 1;
        }
    }
    std::ostream &out = (outfile != "-") ? output : std::cout;

    // Read header
    Header header;
    input.read(reinterpret_cast<char*>(&header), sizeof(Header));

    // Verify magic number
    if (header.magic != MAGIC) {
        std::cerr << "Invalid file format. Magic number doesn't match." << std::endl;
        return 1;
    }

    // Read tree dump
    uint8_t treeDump[MAX_TREE_SIZE];
    input.read(reinterpret_cast<char*>(treeDump), header.tree_size);

    // Reconstruct Huffman tree
    Huffman huffman;
    Node* root = huffman.reconstructTree(treeDump, header.tree_size);

    if (root == nullptr) {
        std::cerr << "Failed to reconstruct Huffman tree." << std::endl;
        return 1;
    }

    // Calculate sizes for statistics
    uint64_t compressed_size = 0;
    if (print_stats) {
        compressed_size = fs::file_size(infile);
    }

    // Create bit reader
    BitReader reader(input);

    // Decode file
    uint64_t decoded_symbols = 0;
    Node* current = root;

    while (decoded_symbols < header.file_size && !reader.eof()) {
        int bit = reader.readBit();
        if (bit == -1) break;

        if (bit == 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->isLeaf()) {
            out.put(current->symbol);
            decoded_symbols++;

            current = root;
        }
    }

    // Print statistics if requested
    if (print_stats) {
        std::cerr << "Compressed file size: " << compressed_size << " bytes" << std::endl;
        std::cerr << "Decompressed file size: " << header.file_size << " bytes" << std::endl;
    }

    delete root;

    return 0;
}