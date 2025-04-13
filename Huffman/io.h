//
// Created by Lucas on 4/13/2025.
//

#ifndef IO_H
#define IO_H

#include <cstdint>
#include <fstream>
#include "define.h"

class BitReader {
private:
    std::ifstream &in;
    uint8_t buffer;
    uint8_t bitPos;
    bool endOfFile;

public:

    BitReader(std::ifstream &infile);

    // Read a single bit from the file
    int readBit();

    // Check if end of file has been reached
    bool eof() const;
};

class BitWriter {
private:
    std::ofstream &out;
    uint8_t buffer;
    uint8_t bitPos;

public:
    // Constructor - takes an output file stream
    BitWriter(std::ofstream &outfile);

    // Destructor - flushes any remaining bits
    ~BitWriter();

    // Write a single bit to the file
    void writeBit(uint8_t bit);

    // Write an entire byte to the file
    void writeByte(uint8_t byte);

    // Flush any bits in the buffer to the file
    void flush();
};

#endif //IO_H