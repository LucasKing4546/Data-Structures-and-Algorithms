#include "Set.h"
#include "SetITerator.h"
#include <cmath>

// Initial capacity of the hash table
const int INITIAL_CAPACITY = 16;
// Load factor threshold
const float LOAD_FACTOR_THRESHOLD = 0.7f;

// Worst case: Theta(cap)
// Average case: Theta(cap)
// Best case: Theta(cap)
Set::Set() {
    // Initialize an empty hash table
    this->capacity = INITIAL_CAPACITY;
    this->table = new Node*[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->table[i] = nullptr;
    }
    this->numElements = 0;
    this->loadFactor = LOAD_FACTOR_THRESHOLD;
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
int Set::hash(TElem elem) const {
    return abs(elem) % this->capacity;
}

// Worst case: Theta(cap + n)
// Average case: O(cap + n)
// Best case: Theta(cap)
void Set::rehash() {
    int oldCapacity = this->capacity;
    Node** oldTable = this->table;

    this->capacity = 2 * oldCapacity;
    this->table = new Node*[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->table[i] = nullptr;
    }

    this->numElements = 0;

    for (int i = 0; i < oldCapacity; i++) {
        Node* current = oldTable[i];
        while (current != nullptr) {
            Node* next = current->next;
            add(current->info);
            delete current;
            current = next;
        }
    }

    delete[] oldTable;
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
bool Set::add(TElem elem) {
    if (search(elem)) {
        return false;
    }

    // Check if rehashing is needed
    if ((float)(this->numElements + 1) / this->capacity > this->loadFactor) {
        rehash();
    }

    // Compute hash value
    int pos = hash(elem);

    Node* newNode = new Node;
    newNode->info = elem;

    // Insert at the beginning of the list (faster)
    newNode->next = this->table[pos];
    this->table[pos] = newNode;

    this->numElements++;

    return true;
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
bool Set::remove(TElem elem) {
    // Compute hash value
    int pos = hash(elem);

    // Find element in the list
    Node* current = this->table[pos];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->info == elem) {
            // Element found, remove it
            if (prev == nullptr) {
                // Element is at the head of the list
                this->table[pos] = current->next;
            } else {
                // Element is in the middle or end of the list
                prev->next = current->next;
            }

            delete current;
            this->numElements--;

            return true;
        }

        prev = current;
        current = current->next;
    }

    // Element not found
    return false;
}

// Worst case: Theta(n)
// Average case: O(n)
// Best case: Theta(1)
bool Set::search(TElem elem) const {
    // Compute hash value
    int pos = hash(elem);

    Node* current = this->table[pos];

    while (current != nullptr) {
        if (current->info == elem) {
            // Element found
            return true;
        }
        current = current->next;
    }

    // Element not found
    return false;
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
int Set::size() const {
    return this->numElements;
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
bool Set::isEmpty() const {
    return this->numElements == 0;
}

// Worst case: Theta(cap + n)
// Average case: O(cap + n)
// Best case: Theta(cap)
Set::~Set() {
    // Deallocate all nodes
    for (int i = 0; i < this->capacity; i++) {
        Node* current = this->table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Deallocate table
    delete[] this->table;
}

// Worst case: Theta(1)
// Average case: Theta(1)
// Best case: Theta(1)
SetIterator Set::iterator() const {
    return SetIterator(*this);
}