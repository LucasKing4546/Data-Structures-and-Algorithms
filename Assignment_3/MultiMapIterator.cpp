#include "MultiMapIterator.h"
#include <stdexcept>
#include "MultiMap.h"

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	first();
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
TElem MultiMapIterator::getCurrent() const {
	if (!valid()) {
		throw std::invalid_argument("Invalid iterator position");
	}

	TKey key = col.data[currentKey].key;
	TValue value = col.data[currentKey].value->elems[currentValue];
	return TElem(key, value);
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
bool MultiMapIterator::valid() const {
	return currentKey != -1 && currentValue != -1;
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
void MultiMapIterator::next() {
	if (!valid()) {
		throw std::invalid_argument("Invalid iterator position");
	}

	int nextValue = col.data[currentKey].value->next[currentValue];

	if (nextValue != -1) {
		currentValue = nextValue;
	} else {
		int nextKey = col.next[currentKey];
		if (nextKey != -1) {
			currentKey = nextKey;
			currentValue = col.data[currentKey].value->head;
		} else {
			currentKey = -1;
			currentValue = -1;
		}
	}
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
void MultiMapIterator::first() {
	currentKey = col.head;
	currentValue = (currentKey != -1) ? col.data[currentKey].value->head : -1;
}