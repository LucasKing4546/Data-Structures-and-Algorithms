//
// Created by Lucas on 4/12/2025.
//

#ifndef CODE_H
#define CODE_H
#include <cstdint>
#include "define.h"


class Code {
public:
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
    // Constructor
    Code();

    // Verify if empty
    bool empty() const;

    // Verify if full
    bool full() const;

    // Returns size
    int size() const;

    // Push bit
    bool push(uint8_t byte);

    // Pop bit
    uint8_t pop();

};

#endif //CODE_H
