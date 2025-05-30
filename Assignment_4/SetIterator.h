#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);

	int currentBucket;       // Current bucket in the hash table
	Set::Node* currentNode;  // Current node in the current bucket
	Set::Node* previousNode; // Previous node in the current bucket

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	void previous();
};