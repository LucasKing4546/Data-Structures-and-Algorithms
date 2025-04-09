#include "SortedBag.h"
#include <iostream>
#include "SortedBagIterator.h"


// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
SortedBag::SortedBag(Relation r) {
	capacity = 1;
	length = 0;
	elements = new TComp[capacity];
	relation = r;
}

// Best-case: Theta(length)
// Worst-case: Theta(length)
// Total: Theta(length)
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
		elements[length++] = e;
	}
	else {
		int left = 0, right = int(length);
		while (left < right) {
			int mid = (left + right) / 2;
			if (relation(elements[mid], e))
				left = mid + 1;
			else
				right = mid;
		}
		for (int i = int(length); i > left; --i) {
			elements[i] = elements[i - 1];
		}
		elements[left] = e;
		length++;
	}
}

// Best-case: Theta(1)
// Worst-case: Theta(length)
// Total: O(length)
bool SortedBag::remove(TComp e) {
	for (int i = 0; i < length; i++) {
		if (elements[i] == e) {
			for (int j = i; j < length - 1; j++) {
				elements[j] = elements[j + 1];
			}
			length--;
			return true;
		}
		if (!relation(elements[i], e)){
			return false;
		}
	}
	return false;
}

// Best-case: Theta(1)
// Worst-case: Theta(log length)
// Total: O(log length)
bool SortedBag::search(TComp elem) const {
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

// Best-case: Theta(1)
// Worst-case: Theta(length)
// Total: O(length)
int SortedBag::nrOccurrences(TComp elem) const {
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (elements[i] == elem) {
			count++;
		}
		if (!relation(elements[i], elem)) {
			break;
		}
	}
	return count;

}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
int SortedBag::size() const {
	return int(length);
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
bool SortedBag::isEmpty() const {
	return (length == 0);
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

// Best-case: Theta(1)
// Worst-case: Theta(1)
// Total: Theta(1)
SortedBag::~SortedBag() {
	if (elements) {
		delete[] elements;
		elements = nullptr;
	}
}
