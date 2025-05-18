#pragma once
#include <vector>
#include <utility>

using namespace std;

// DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

typedef bool(*Condition)(TValue);
class MultiMapIterator;

struct ValueSLLA {
    int cap;
    TValue* elems;
    int* next;
    int head;
    int firstEmpty;

    ValueSLLA() {
        this->cap = 10;
        elems = new TValue[cap + 1];
        next = new int[cap + 1];
        head = -1;
        for (int i = 1; i < cap; i++) {
            next[i] = i + 1;
        }
        next[cap] = -1;
        firstEmpty = 1;
    }

    void resize();
    void InsertValue(TValue value);
    bool DeleteValue(TValue value);
    vector<TValue> ReturnValues();
    bool isEmpty() const { return head == -1; }

    ~ValueSLLA() {
        delete[] elems;
        delete[] next;
    }
};

struct KeyNode {
    TKey key;
    ValueSLLA* value;

    KeyNode() {
        this->key = NULL_TVALUE;
        this->value = new ValueSLLA();
    }

    KeyNode(TKey key) {
        this->key = key;
        this->value = new ValueSLLA();
    }

    // Copy constructor
    KeyNode(const KeyNode& other) {
        this->key = other.key;
        this->value = new ValueSLLA();

        if (other.value != nullptr) {
            int current = other.value->head;
            while (current != -1) {
                this->value->InsertValue(other.value->elems[current]);
                current = other.value->next[current];
            }
        }
    }

    // Assignment operator
    KeyNode& operator=(const KeyNode& other) {
        if (this != &other) {
            this->key = other.key;

            delete this->value;

            this->value = new ValueSLLA();

            if (other.value != nullptr) {
                int current = other.value->head;
                while (current != -1) {
                    this->value->InsertValue(other.value->elems[current]);
                    current = other.value->next[current];
                }
            }
        }
        return *this;
    }

    ~KeyNode() {
        delete value;
    }
};

class MultiMap {
    friend class MultiMapIterator;
private:
    int cap;
    KeyNode* data;
    int* next;
    int head;
    int firstEmpty;
    int count;

    void resize();
    int findKey(TKey c) const; // Helper method to find key position
    
public:
    // Constructor
    MultiMap();

    // Adds a key value pair to the multimap
    void add(TKey c, TValue v);

    // Removes a key value pair from the multimap
    // Returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    // Returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector<TValue> search(TKey c) const;

    // Returns the number of pairs from the multimap
    int size() const;

    // Checks whether the multimap is empty
    bool isEmpty() const;

    // Returns an iterator for the multimap
    MultiMapIterator iterator() const;

    // Destructor
    ~MultiMap();

    // Filter
    void filter(Condition cond);
};