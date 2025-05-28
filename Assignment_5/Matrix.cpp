#include "Matrix.h"
#include <exception>
using namespace std;

Node* Matrix::search(Node* current, int i, int j) const {
	if (current == nullptr)
		return nullptr;

	if (current->row == i && current->col == j)
		return current;

	if (i > current->row || (i == current->row && j > current->col))
		return search(current->left, i, j);
	else
		return search(current->right, i, j);
}


bool Matrix::insert(Node*& current, int i, int j, TElem e) {
	if (current == nullptr) {
		current = new Node(i, j, e);
		return true;
	}

	if (i > current->row || (i == current->row && j > current->col))
		return insert(current->left, i, j, e);
	else if (i == current->row && j == current->col) {
		current->value = e;
		return true;
	} else {
		return insert(current->right, i, j, e);
	}
}



Matrix::Matrix(int nrLines, int nrCols) {
	lines = nrLines;
	columns = nrCols;
    root = nullptr; // Initialize the root node
}

int Matrix::nrLines() const {
	return lines;
}


int Matrix::nrColumns() const {
	return columns;
}


TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= lines || j < 0 || j >= columns)
		throw std::exception();
	Node* found = search(root, i, j);
	if (found != nullptr)
		return found->value;
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= lines || j < 0 || j >= columns)
		throw std::exception();
	Node* found = search(root, i, j);
	TElem old = NULL_TELEM;
	if (found != nullptr) {
		old = found->value;
	}
	insert(root, i, j, e);
	return old;
}


