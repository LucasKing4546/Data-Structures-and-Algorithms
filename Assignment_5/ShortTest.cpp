#include <algorithm>
#include <assert.h>
#include "Matrix.h"
#include "MatrixIterator.h"
#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

	MatrixIterator it(m);
	int count = 0;
	while (it.valid()) {
        TElem current = it.getCurrent();
        if (current != NULL_TELEM) {
            count++;
        }
        it.next();
    }
	assert(count == 1);
}