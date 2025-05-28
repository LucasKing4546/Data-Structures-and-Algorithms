//
// Created by Lucas on 5/28/2025.
//

#ifndef MATRIXITERATOR_H
#define MATRIXITERATOR_H
#pragma once
#include "Matrix.h"

class MatrixIterator {
private:
    const Matrix& matrix;
    int currentRow;
    int currentCol;

public:
    // Constructor
    MatrixIterator(const Matrix& m);

    // Returns the current element
    TElem getCurrent() const;

    // Checks if the iterator is valid
    bool valid() const;

    // Moves to the next element
    void next();

    // Moves to the first element
    void first();
};
#endif //MATRIXITERATOR_H
