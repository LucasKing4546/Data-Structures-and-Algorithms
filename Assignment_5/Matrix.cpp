#include "Matrix.h"
#include <exception>
using namespace std;

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
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

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
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

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
Node* Matrix::findMin(Node* current) const {
	while (current && current->left != nullptr) {
		current = current->left;
	}
	return current;
}

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
bool Matrix::remove(Node*& current, int i, int j) {
	if (current == nullptr)
		return false;

	if (i > current->row || (i == current->row && j > current->col)) {
		return remove(current->left, i, j);
	}
	else if (i < current->row || (i == current->row && j < current->col)) {
		return remove(current->right, i, j);
	}
	else {
		if (current->left == nullptr) {
			Node* temp = current->right;
			delete current;
			current = temp;
		}
		else if (current->right == nullptr) {
			Node* temp = current->left;
			delete current;
			current = temp;
		}
		else {
			Node* successor = findMin(current->right);

			current->row = successor->row;
			current->col = successor->col;
			current->value = successor->value;

			remove(current->right, successor->row, successor->col);
		}
		return true;
	}
}


// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	lines = nrLines;
	columns = nrCols;
    root = nullptr; // Initialize the root node
}

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
int Matrix::nrLines() const {
	return lines;
}

// Best Case: Theta(1)
// Average Case: Theta(1)
// Worst Case: Theta(1)
int Matrix::nrColumns() const {
	return columns;
}

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= lines || j < 0 || j >= columns)
		throw std::exception();
	Node* found = search(root, i, j);
	if (found != nullptr)
		return found->value;
	return NULL_TELEM;
}

// Best Case: Theta(1)
// Average Case: O(log n)
// Worst Case: Theta(n)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= lines || j < 0 || j >= columns)
		throw std::exception();
	Node* found = search(root, i, j);
	TElem old = NULL_TELEM;
	if (found != nullptr) {
		old = found->value;
	}
	if (e == NULL_TELEM) {
		if (found != nullptr) {
			remove(root, i, j);
			return old;
		}
		return NULL_TELEM; // No change if the element is already NULL_TELEM
	}
	insert(root, i, j, e);
	return old;
}


