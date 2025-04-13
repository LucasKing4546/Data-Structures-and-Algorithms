//
// Created by Lucas on 4/12/2025.
//
#ifndef DEFINE_H
#define DEFINE_H

#include <filesystem>
#include <cstdint>

#define BLOCK 4096 // 4KB blocks - read blocks of data from the file
#define ALPHABET 256 // ASCII + Extended ASCII.
#define MAGIC 0xDEADEAEF // 32-bit magic number.
#define MAX_CODE_SIZE (ALPHABET / 8) // Bytes for a maximum, 256-bit code.
#define MAX_TREE_SIZE (3 * ALPHABET - 1) // Maximum Huffman tree dump size

namespace fs = std::filesystem;

typedef struct {
  uint32_t magic;
  uint32_t tree_size;
  uint64_t file_size;
} Header;

#endif //DEFINE_H
