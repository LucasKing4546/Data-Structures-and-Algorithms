#include "Set.h"
#include "SetITerator.h"
#include <cmath>

// Initial capacity of the hash table
const int INITIAL_CAPACITY = 16;
// Load factor threshold
const float LOAD_FACTOR_THRESHOLD = 0.7f;

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

int Set::hash(TElem elem) const {
    return abs(elem) % this->capacity;
}

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

        // Move to next node
        prev = current;
        current = current->next;
    }

    // Element not found
    return false;
}

bool Set::search(TElem elem) const {
    // Compute hash value
    int pos = hash(elem);

    // Search in the list
    Node* current = this->table[pos];

    while (current != nullptr) {
        if (current->info == elem) {
            // Element found
            return true;
        }
        // Move to next node
        current = current->next;
    }

    // Element not found
    return false;
}

int Set::size() const {
    return this->numElements;
}

bool Set::isEmpty() const {
    return this->numElements == 0;
}

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

SetIterator Set::iterator() const {
    return SetIterator(*this);
}