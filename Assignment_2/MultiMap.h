#pragma once
#include <set>
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
typedef bool (*Condition)(TKey);
class MultiMapIterator;

struct ValueNode {
	TValue data;
	ValueNode* next;
	ValueNode* prev;
	ValueNode(TValue value, ValueNode* n = nullptr, ValueNode* p = nullptr) : data(TValue(value)), next(n), prev(p) {}
};

struct KeyNode {
	TKey key;
	ValueNode* first;
	ValueNode* last;
	KeyNode* next;
	KeyNode* prev;
	KeyNode(TKey key,
		ValueNode* first = nullptr,
		ValueNode* last = nullptr,
		KeyNode* next = nullptr,
		KeyNode* prev = nullptr) : key(key), first(first), last(last), next(next), prev(prev){}
};

class MultiMap
{
	friend class MultiMapIterator;

private:
	KeyNode* head;
	KeyNode* tail;
	int count;
	set<TKey> keys;

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//keeps in the MultiMap only those pairs whose key respects the given condition
	void filter(Condition cond);

	//descturctor
	~MultiMap();
};


