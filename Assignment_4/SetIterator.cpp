#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set& m) : set(m){
	this->currentBucket = 0;
	this->currentNode = nullptr;

	first();
}

void SetIterator::first() {
	this->currentBucket = 0;
	this->currentNode = nullptr;

	// Find the first non-empty bucket
	while (currentBucket < set.capacity && set.table[currentBucket] == nullptr) {
		currentBucket++;
	}

	// If we found a non-empty bucket, set current node to its first element
	if (currentBucket < set.capacity) {
		currentNode = set.table[currentBucket];
	}
}

void SetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	if (currentNode->next != nullptr) {
		currentNode = currentNode->next;
		return;
	}

	currentBucket++;
	while (currentBucket < set.capacity && set.table[currentBucket] == nullptr) {
		currentBucket++;
	}

	if (currentBucket < set.capacity) {
		currentNode = set.table[currentBucket];
	} else {
		currentNode = nullptr;
	}
}

TElem SetIterator::getCurrent()
{
	if (!valid()) {
		throw std::exception();
	}

	return currentNode->info;
}

bool SetIterator::valid() const {
	return currentNode != nullptr;
}