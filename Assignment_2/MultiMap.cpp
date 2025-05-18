#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	head = nullptr;
	tail = nullptr;
	count = 0;
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
bool MultiMap::find(TKey c) const {
	KeyNode* currentNode = head;
	while (currentNode != nullptr && currentNode->key != c) {
		currentNode = currentNode->next;
	}
	if (currentNode == nullptr) {
		return false;
	}
	return true;
}



void MultiMap::add(TKey c, TValue v) {
	// Worst case: Theta(n)
	// Average case: O(n)
	// Best case: Theta(1)
	if (!find(c)) {
		KeyNode* newNode = new KeyNode(c);
		ValueNode* newValueNode = new ValueNode(v);

		newNode->next = nullptr;
		newNode->prev = tail;

		newNode->first = newValueNode;
		newNode->last = newNode->first;
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}
	else {
		KeyNode* currentNode = head;
		while (currentNode != nullptr && currentNode->key != c) {
			currentNode = currentNode->next;
		}
		if (currentNode != nullptr) {
			ValueNode* newValueNode = new ValueNode(v);
			if (currentNode->first == nullptr) {
				currentNode->first = newValueNode;
				currentNode->first->prev = nullptr;
				currentNode->first->next = nullptr;
				currentNode->last = currentNode->first;
			}
			else {
				currentNode->last->next = newValueNode;
				currentNode->last->next->prev = currentNode->last;
				currentNode->last = currentNode->last->next;
			}
			count++;
		}
	}
}


bool MultiMap::remove(TKey c, TValue v) {
	// n - number of nodes
	// v - number of values
	// Worst case: Theta(n + v)
	// Average case: O(n + v)
	// Best case: Theta(1)
	KeyNode* currentNode = head;

	while (currentNode != nullptr && currentNode->key != c) {
		currentNode = currentNode->next;
	}
	if (currentNode != nullptr) {
		ValueNode* valueNode = currentNode->first;
		while (valueNode != nullptr && valueNode->data != v) {
			valueNode = valueNode->next;
		}
		if (valueNode == nullptr) {
			return false;
		}
		if (valueNode == currentNode->first && valueNode == currentNode->last) {
			currentNode->first = nullptr;
			currentNode->last = nullptr;
			if (currentNode == head && currentNode == tail) {
				head = nullptr;
				tail = nullptr;
			} else if (currentNode == head) {
				head = currentNode->next;
				head->prev = nullptr;
			} else if (currentNode == tail) {
				tail = currentNode->prev;
				tail->next = nullptr;
			}
			else {
				currentNode->prev->next = currentNode->next;
				currentNode->next->prev = currentNode->prev;
			}
			delete currentNode;
		} else if (currentNode->first == valueNode) {
			currentNode->first = valueNode->next;
			currentNode->first->prev = nullptr;
		} else if (currentNode->last == valueNode) {
			currentNode->last = valueNode->prev;
			currentNode->last->next = nullptr;
		} else {
			valueNode->prev->next = valueNode->next;
			valueNode->next->prev = valueNode->prev;
		}
		count--;
		delete valueNode;
		return true;
	}
	return false;
}


vector<TValue> MultiMap::search(TKey c) const {
	// Worst case: Theta(n)
	// Average case: O(n)
	// Best case: Theta(1)
	vector<TValue> result;
	KeyNode* currentNode = head;
	while (currentNode != nullptr && currentNode->key != c) {
		currentNode = currentNode->next;
	}
	if (currentNode != nullptr) {
		ValueNode* valueNode = currentNode->first;
		while (valueNode != nullptr) {
			result.push_back(valueNode->data);
			valueNode = valueNode->next;
		}
	}
	return result;
}


int MultiMap::size() const {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	return count;
}


bool MultiMap::isEmpty() const {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	return count == 0;
}

MultiMapIterator MultiMap::iterator() const {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	return MultiMapIterator(*this);
}

void MultiMap::filter(Condition cond) {
	// Worst case: Theta(n)
	// Average case: Theta(n)
	// Best case: Theta(n)
	KeyNode* currentNode = head;
	while (currentNode!=nullptr) {
		if (!cond(currentNode->key)) {
			if (currentNode == head && currentNode == tail) {
				head = nullptr;
				tail = nullptr;
			} else if (currentNode == head) {
				head = currentNode->next;
				head->prev = nullptr;
			} else if (currentNode == tail) {
				tail = currentNode->prev;
				tail->next = nullptr;
			} else {
				currentNode->prev->next = currentNode->next;
				currentNode->next->prev = currentNode->prev;
			}
			count--;
		}
		currentNode = currentNode->next;
	}
	delete currentNode;
}


MultiMap::~MultiMap() {
	// Worst case: Theta(1)
	// Average case: Theta(1)
	// Best case: Theta(1)
	KeyNode* currentNode = head;
	while (currentNode != nullptr) {
		KeyNode* temp = currentNode;
		currentNode = currentNode->next;
		delete temp;
	}
}

