//
// Created by Lucas on 4/13/2025.
//

#include "io.h"

BitReader::BitReader(std::ifstream &infile):
in(infile),
buffer(0),
bitPos(0),
endOfFile(false)
{}

bool BitReader::eof() const {
    return endOfFile;
}

int BitReader::readBit() {
    if (bitPos == 0) {
        in.read((char *) &buffer, 1);
        if (in.eof()) {
            endOfFile = true;
            return -1;
        }
        bitPos = 8;
    }
    bitPos--;
    return (buffer >> bitPos) & 1;
}

BitWriter::BitWriter(std::ofstream &outfile): out(outfile), buffer(0), bitPos(0) {}

BitWriter::~BitWriter() {
    flush();
}

void BitWriter::writeBit(uint8_t bit) {
    uint8_t mask = bit << (7-bitPos);
    buffer |= mask;
    bitPos++;
    if (bitPos == 8) {
        out.write((char *) &buffer, 1);
        buffer = 0;
        bitPos = 0;
    }
}

void BitWriter::writeByte(uint8_t byte) {
    out.write((char *) &byte, 1);
}

void BitWriter::flush() {
    if (bitPos > 0) {
        out.write((char *) &buffer, 1);
        buffer = 0;
        bitPos = 0;
    }
}



