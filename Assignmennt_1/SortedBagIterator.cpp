#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	currentPosition = 0;
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (currentPosition >= bag.size()) {
		throw out_of_range("No more elements in the bag");
	}
	return bag.elements[currentPosition];
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
bool SortedBagIterator::valid() {
	if (currentPosition < bag.size() && currentPosition >= 0) {
		return true;
	}
	return false;
}

// Best-case: Theta(1)
// Worst-case: Theta(k)
// Total: O(k)
void SortedBagIterator::back(int k) {
	if (k < 1) {
		throw std::invalid_argument("k must be greater than zero");
	}
	while (k) {
		if (currentPosition < 0) {
			throw out_of_range("No more elements in the bag");
		}
		currentPosition--;
		k--;
	}
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
void SortedBagIterator::next() {
	if (currentPosition >= bag.size()) {
		throw out_of_range("No more elements in the bag");	}
	else {
		currentPosition++;
	}
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
void SortedBagIterator::first() {
	currentPosition = 0;
}

