#include "MultiMapIterator.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	current = col.head;
	currentValue = (current != nullptr) ? current->first : nullptr;
}

TElem MultiMapIterator::getCurrent() const{
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	if (current == nullptr) {
		throw std::out_of_range("Invalid iterator");
	}
	return TElem(current->key, currentValue->data);
}

bool MultiMapIterator::valid() const {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	if (current != nullptr) {
		return true;
	}
	return false;
}

void MultiMapIterator::next() {
	if (current == nullptr) {
		throw std::out_of_range("Invalid iterator");
	}
	if (currentValue == nullptr || currentValue->next == nullptr) {
		current = current->next;
		currentValue = (current != nullptr) ? current->first : nullptr;
	} else {
		currentValue = currentValue->next;
	}
}

void MultiMapIterator::first() {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	current = col.head;
	currentValue = (current != nullptr) ? current->first : nullptr;
}

