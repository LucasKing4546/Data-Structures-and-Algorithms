#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	// Theta(1)
	currentPosition = 0;
}

TComp SortedBagIterator::getCurrent() {
	// Theta(1)
	if (currentPosition >= bag.size()) {
		throw out_of_range("No more elements in the bag");
	}
	return bag.elements[currentPosition];
}

bool SortedBagIterator::valid() {
	// Theta(1)
	if (currentPosition < bag.size()) {
		return true;
	}
	return false;
}

void SortedBagIterator::next() {
	// Theta(1)
	if (currentPosition >= bag.size()) {
		throw out_of_range("No more elements in the bag");	}
	else {
		currentPosition++;
	}
}

void SortedBagIterator::first() {
	// Theta(1)
	currentPosition = 0;
}

