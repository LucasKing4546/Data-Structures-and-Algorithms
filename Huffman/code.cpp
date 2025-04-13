//
// Created by Lucas on 4/12/2025.
//

#include "code.h"

Code::Code() {
    this->top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; i++) {
        this->bits[i] = 0;
    }
}

bool Code::empty() const {
    return this->top == 0;
}

bool Code::full() const {
    return this->top == MAX_CODE_SIZE;
}

int Code::size() const {
    return this->top;
}

bool Code::push(uint8_t byte) {
    if (this->top == MAX_CODE_SIZE) {
        return false;
    }
    this->bits[this->top++] = byte;
    return true;
}

uint8_t Code::pop() {
    if (this->top == 0) {
        return 0;
    }
    uint8_t byte = this->bits[--this->top];
    this->bits[this->top] = 0;
    return byte;
}


