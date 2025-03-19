#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0)
	{
		throw exception();
	}
	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)


FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
	delete[] this->elements;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)


bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	if (this->mapSize == this->capacity)
	{
		throw exception();
	}
	int count = 0;
	int index = 0;
	while (count < 2 && index < this->mapSize)
	{
		if (this->elements[index].first == c) {
			count++;
		}
		index++;
	}
	if (count == 2)
	{
		return false;
	}
	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}
// BC: Theta(1) - when the first two keys from the map are equal to c
// WC: Theta(mapSize) - when the key c appears only once or zero times in the map
// TC: O(mapSize)


ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int nrfound = 0;
	int index = 0;
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c)
		{
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
			}
		}
		index++;
	}
	return result;
}
// BC: Theta(1) - when the first two keys from the map are equal to c
// WC: Theta(mapSize) - when the key c appears only once or zero times in the map
// TC: O(mapSize)


bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	int index = 0;
	while (index < this->mapSize)
	{
		if (this->elements[index].first == c && this->elements[index].second == v)
		{
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
		index++;
	}
	return false;
}
// BC: Theta(1) - when the pair we want to remove is on the first position
// WC: Theta(mapSize) - when the pair is not in the array or it is on the last position
// TC: O(mapSize)


int FixedCapBiMap::size() const {
	//TODO - Implementation
	return this->mapSize;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)


bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return this->mapSize == 0;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)


bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return this->mapSize == this->capacity;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)


FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)