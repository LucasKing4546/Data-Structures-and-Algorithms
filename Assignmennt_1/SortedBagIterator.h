#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	int currentPosition;
public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	void back(int k);
};

