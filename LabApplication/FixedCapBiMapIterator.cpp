#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	//TODO - Implementation
	this->currentPosition = 0;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)



void FixedCapBiMapIterator::first() {
	//TODO - Implementation
	this->currentPosition = 0;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)



void FixedCapBiMapIterator::next() {
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	this->currentPosition++;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)



TElem FixedCapBiMapIterator::getCurrent(){
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	return this->map.elements[this->currentPosition];
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)



bool FixedCapBiMapIterator::valid() const {
	//TODO - Implementation
	return this->currentPosition < this->map.mapSize;
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)