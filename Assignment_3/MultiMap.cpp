#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Worst case: Theta(n)
//Average case: Theta(n)
//Best case: Theta(n)
void ValueSLLA::resize() {
    int new_capacity = cap * 2;
    TValue* newElems = new TValue[new_capacity + 1];
    int* newNext = new int[new_capacity + 1];

    for(int i = 1; i <= cap; i++) {
        newNext[i] = next[i];
        newElems[i] = elems[i];
    }

    for (int i = cap + 1; i <= new_capacity; i++) {
        newNext[i] = i + 1;
    }
    newNext[new_capacity] = -1;

    delete[] elems;
    delete[] next;

    elems = newElems;
    next = newNext;
    firstEmpty = cap + 1;
    cap = new_capacity;
}

//Worst case: O(n)
//Average case: O(1)
//Best case: Theta(1)
void ValueSLLA::InsertValue(TValue value) {
    if (firstEmpty == -1) {
        resize();
    }

    int newPos = firstEmpty;
    firstEmpty = next[firstEmpty];

    elems[newPos] = value;

    next[newPos] = head;
    head = newPos;
}

//Worst case: O(n)
//Average case: O(n)
//Best case: Theta(1)
bool ValueSLLA::DeleteValue(TValue value) {
    int current = head;
    int previous = -1;

    while (current != -1 && elems[current] != value) {
        previous = current;
        current = next[current];
    }

    if (current == -1) {
        return false;
    }

    if (previous == -1) {
        // First node
        head = next[current];
    } else {
        // Middle or last node
        next[previous] = next[current];
    }

    next[current] = firstEmpty;
    firstEmpty = current;

    return true;
}

//Worst case: Theta(n)
//Average case: Theta(n)
//Best case: Theta(n)
vector<TValue> ValueSLLA::ReturnValues() {
    vector<TValue> result;
    int current = head;
    while (current != -1) {
        result.push_back(elems[current]);
        current = next[current];
    }
    return result;
}

//Worst case: Theta(n)
//Average case: Theta(n)
//Best case: Theta(n)
void MultiMap::resize() {
    int new_capacity = cap * 2;
    KeyNode* newData = new KeyNode[new_capacity + 1];
    int* newNext = new int[new_capacity + 1];

    for(int i = 1; i <= cap; i++) {
        newData[i] = data[i];
        newNext[i] = next[i];

        data[i].value = nullptr;
    }

    for (int i = cap + 1; i <= new_capacity; i++) {
        newNext[i] = i + 1;
    }
    newNext[new_capacity] = -1;

    delete[] data;
    delete[] next;

    data = newData;
    next = newNext;
    firstEmpty = cap + 1;
    cap = new_capacity;
}

//Worst case: Theta(cap)
//Average case: Theta(cap)
//Best case: Theta(cap)
MultiMap::MultiMap() {
    cap = 10;
    data = new KeyNode[cap + 1];
    next = new int[cap + 1];
    head = -1;

    for (int i = 1; i < cap; i++) {
        next[i] = i + 1;
    }
    next[cap] = -1;
    firstEmpty = 1;
    count = 0;
}

//Worst case: Theta(n)
//Average case: O(n)
//Best case: Theta(1)
int MultiMap::findKey(TKey c) const {
    int current = head;
    while (current != -1) {
        if (data[current].key == c) {
            return current;
        }
        current = next[current];
    }
    return -1;
}

//Worst case: O(n)
//Average case: O(n)
//Best case: O(n)
void MultiMap::add(TKey c, TValue v) {
    int keyPosition = findKey(c);

    if (keyPosition != -1) {
        data[keyPosition].value->InsertValue(v);
        count++;
        return;
    }

    if (firstEmpty == -1) {
        resize();
    }

    int newPos = firstEmpty;
    firstEmpty = next[firstEmpty];

    data[newPos].key = c;
    data[newPos].value->InsertValue(v);

    next[newPos] = head;
    head = newPos;

    count++;
}

//Worst case: O(n)
//Average case: O(n)
//Best case: O(n)
bool MultiMap::remove(TKey c, TValue v) {
    int keyPosition = findKey(c);

    if (keyPosition == -1) {
        return false;
    }

    bool deleted = data[keyPosition].value->DeleteValue(v);
    if (!deleted) {
        return false;
    }

    count--;

    if (data[keyPosition].value->isEmpty()) {
        int current = head;
        int previous = -1;

        while (current != keyPosition) {
            previous = current;
            current = next[current];
        }

        if (previous == -1) {
            // First node
            head = next[head];
        } else {
            // Middle or last node
            next[previous] = next[current];
        }

        next[current] = firstEmpty;
        firstEmpty = current;
    }

    return true;
}

//Worst case: O(n)
//Average case: O(n)
//Best case: O(n)
vector<TValue> MultiMap::search(TKey c) const {
    int keyPosition = findKey(c);

    if (keyPosition != -1) {
        return data[keyPosition].value->ReturnValues();
    }

    return vector<TValue>();
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
int MultiMap::size() const {
    return count;
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
bool MultiMap::isEmpty() const {
    return count == 0;
}

//Worst case: Theta(1)
//Average case: Theta(1)
//Best case: Theta(1)
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

//Worst case: Theta(n)
//Average case: Theta(n)
//Best case: Theta(n)
MultiMap::~MultiMap() {
    for (int i = 1; i <= cap; i++) {
        delete data[i].value;
        data[i].value = nullptr; // Prevent double deletion issues
    }
    delete[] data;
    delete[] next;
}

//Worst case: Theta(n)
//Average case: Theta(n)
//Best case: Theta(n)
void MultiMap::filter(Condition cond) {
    std::vector<std::pair<TKey, TValue>> toRemove;

    MultiMapIterator it = MultiMapIterator(*this);
    while (it.valid()) {
        TElem current = it.getCurrent();
        if (!cond(current.second)) {
            toRemove.push_back(current);
        }
        it.next();
    }

    for (const auto& pair : toRemove) {
        remove(pair.first, pair.second);
    }
}