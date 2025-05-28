//
// Created by Lucas on 5/28/2025.
//
#include "MatrixIterator.h"
#include <exception>

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
MatrixIterator::MatrixIterator(const Matrix& m) : matrix(m) {
    first();
}

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
TElem MatrixIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return matrix.element(currentRow, currentCol);
}

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
bool MatrixIterator::valid() const {
    return currentRow < matrix.nrLines() && currentCol < matrix.nrColumns() &&
           currentRow >= 0 && currentCol >= 0;
}

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
void MatrixIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    currentCol++;
    if (currentCol >= matrix.nrColumns()) {
        currentCol = 0;
        currentRow++;
    }
}

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
void MatrixIterator::first() {
    currentRow = 0;
    currentCol = 0;
}