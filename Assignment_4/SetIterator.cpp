#include "SetIterator.h"
#include "Set.h"
#include <exception>

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
SetIterator::SetIterator(const Set& m) : set(m){
	this->currentBucket = 0;
	this->currentNode = nullptr;
	this->previousNode = nullptr;
	first();
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
void SetIterator::first() {
	this->currentBucket = 0;
	this->currentNode = nullptr;
	this->previousNode = nullptr;

	// Find the first non-empty bucket
	while (currentBucket < set.capacity && set.table[currentBucket] == nullptr) {
		currentBucket++;
	}

	// If we found a non-empty bucket, set current node to its first element
	if (currentBucket < set.capacity) {
		currentNode = set.table[currentBucket];
	}
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
void SetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	if (currentNode->next != nullptr) {
		previousNode = currentNode;
		currentNode = currentNode->next;
		return;
	}

	currentBucket++;
	while (currentBucket < set.capacity && set.table[currentBucket] == nullptr) {
		currentBucket++;
	}

	if (currentBucket < set.capacity) {
		previousNode = nullptr;
		currentNode = set.table[currentBucket];
	} else {
		previousNode = nullptr;
		currentNode = nullptr;
	}
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
TElem SetIterator::getCurrent(){
	if (!valid()) {
		throw std::exception();
	}

	return currentNode->info;
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
bool SetIterator::valid() const {
	return currentNode != nullptr;
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
void SetIterator::previous() {
	if (!valid() || previousNode == nullptr) {
		throw std::exception();
	}

	currentNode = previousNode;

	// If current is now the first in the bucket, previousNode becomes nullptr
	if (currentNode == set.table[currentBucket]) {
		previousNode = nullptr;
	} else {
		// Find the node before current in the bucket
		previousNode = set.table[currentBucket];
		while (previousNode->next != currentNode) {
			previousNode = previousNode->next;
		}
	}
}