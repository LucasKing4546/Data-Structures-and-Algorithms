//
// Created by Lucas on 4/13/2025.
//
#include <fstream>
#include <iostream>
#include <filesystem>
#include <getopt.h>
#include <vector>
#include <memory>

#include "define.h"
#include "huffman.h"
#include "io.h"

void print_help() {
    std::cout << "  A Huffman encoder.\n\n"
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

    if (root->isLeaf()) {
        tree_dump.push_back('L');
        tree_dump.push_back(root->symbol);
    } else {
        tree_dump.push_back('I');
    }
}

int main(int argc, char *argv[]) {
    std::string infile = "-";  // Default to stdin
    std::string outfile = "";
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
    infile = "input.txt";
    outfile = "compressed.bin";
    if (outfile.empty()) {
        std::cerr << "Output file must be specified." << std::endl;
        return 1;
    }
    // Prepare input stream
    std::ifstream input_file;
    if (infile != "-") {
        input_file.open(infile);
        if (!input_file.is_open()) {
            std::cerr << "Could not open input file: " << infile << std::endl;
            return 1;
        }
    }
    std::istream &input = (infile != "-") ? input_file : std::cin;

    // Create histogram and read file into memory if stdin
    uint64_t histogram[ALPHABET] = {0};
    std::vector<uint8_t> file_contents;

    // Increment positions 0 and 255 as required
    histogram[0]++;
    histogram[255]++;

    // Read input and build histogram
    uint8_t byte;
    uint64_t file_size = 0;

    if (infile != "-") {
        // For regular files, just read and count
        while (input.read(reinterpret_cast<char*>(&byte), 1)) {
            histogram[byte]++;
            file_size++;
        }
        input_file.clear();
        input_file.seekg(0); // Reset the pointer, so we can read the file again
    } else {
        // For stdin, store contents as we read
        while (input.read(reinterpret_cast<char*>(&byte), 1)) {
            histogram[byte]++;
            file_contents.push_back(byte);
            file_size++;
        }
    }

    // Build Huffman tree and code table
    Huffman huffman;
    Node* root = huffman.buildTree(histogram);
    if (root == nullptr) {
        std::cerr << "Failed to build Huffman tree." << std::endl;
        return 1;
    }

    Code codeTable[ALPHABET];
    huffman.buildCodeTable(root, codeTable);

    // Create tree dump
    std::vector<uint8_t> tree_dump;
    dumpTree(root, tree_dump);

    // Open output file
    std::ofstream output(outfile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Could not open output file: " << outfile << std::endl;
        delete root;
        return 1;
    }

    // Create and write header
    Header header;
    header.magic = MAGIC;
    header.tree_size = tree_dump.size();
    header.file_size = file_size;

    output.write(reinterpret_cast<char*>(&header), sizeof(Header));

    output.write(reinterpret_cast<char*>(tree_dump.data()), tree_dump.size());

    BitWriter writer(output);

    // Encode file
    if (infile != "-") {
        // For regular files, read again and encode
        while (input_file.read(reinterpret_cast<char*>(&byte), 1)) {
            Code code = codeTable[byte];
            for (int i = 0; i < code.size(); i++) {
                writer.writeBit(code.bits[i]);
            }
        }
    } else {
        // For stdin, use stored content
        for (uint8_t byte : file_contents) {
            Code code = codeTable[byte];
            for (int i = 0; i < code.size(); i++) {
                writer.writeBit(code.bits[i]);
            }
        }
    }

    writer.flush();

    // Calculate total output size for statistics
    output.flush();
    uint64_t compressed_size = sizeof(Header) + tree_dump.size();
    if (outfile != "-") {
        compressed_size = fs::file_size(outfile);
    }

    if (print_stats) {
        std::cerr << "Uncompressed file size: " << file_size << " bytes" << std::endl;
        std::cerr << "Compressed file size: " << compressed_size << " bytes" << std::endl;
    }


    delete root;

    return 0;
}