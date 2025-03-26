#include "SortedBag.h"
#include <iostream>
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	// Theta(1)
	capacity = 1;
	length = 0;
	elements = new TComp[capacity];
	relation = r;
}

void SortedBag::add(TComp e) {
	// If resize is needed, copying takes Theta(length)
	if (length == capacity) {
		unsigned int new_capacity = capacity * 2;
		TComp* new_elements = new TComp[new_capacity];
		for (int i = 0; i < length; i++) {
			new_elements[i] = elements[i];
		}
		delete[] elements;
		elements = new_elements;
		capacity = new_capacity;
	}

	if (length == 0) {
		// Theta(1)
		elements[length++] = e;
	}
	else {
		// Theta(log length)
		int left = 0, right = int(length);
		while (left < right) {
			int mid = (left + right) / 2;
			if (relation(elements[mid], e))
				left = mid + 1;
			else
				right = mid;
		}
		// O(length)
		for (int i = int(length); i > left; --i) {
			elements[i] = elements[i - 1];
		}
		elements[left] = e;
		length++;
	}

	//Overall complexity: Theta(length)
}


bool SortedBag::remove(TComp e) {
	// Theta(length)
	for (int i = 0; i < length; i++) {
		if (elements[i] == e) {
			// Theta(n): Worst-case shifting of elements left after removal
			for (int j = i; j < length - 1; j++) {
				elements[j] = elements[j + 1];
			}
			length--;
			return true;
		}
	}
	return false;
}


bool SortedBag::search(TComp elem) const {
	// Theta(log length)
	int left = 0, right = int(length - 1);
	while (left <= right) {
		int mid = (left + right) / 2;
		if (elem == elements[mid]) {
			return true;
		}
		if (relation(elements[mid], elem)) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	// Theta(length)
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (elements[i] == elem) {
			count++;
		}
	}
	return count;
}


int SortedBag::size() const {
	// Theta(1)
	return int(length);
}


bool SortedBag::isEmpty() const {
	// Theta(1)
	return (length == 0);
}


SortedBagIterator SortedBag::iterator() const {
	// Theta(1)
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	// Theta(1)
	if (elements) {
		delete[] elements;
		elements = nullptr;
	}
}
