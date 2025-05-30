#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
struct Node {
	int row, col;
	TElem value;
	Node* left, *right;
	Node() : row(0), col(0), value(NULL_TELEM), left(nullptr), right(nullptr) {}
	Node(int r, int c, TElem v) : row(r), col(c), value(v), left(nullptr), right(nullptr) {}
};
class Matrix {
private:
  	int lines, columns;
    Node* root;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    // helper function
	Node* search(Node* current, int i, int j) const;
	bool insert(Node*& current, int i, int j, TElem e);
	bool remove(Node*& current, int i, int j);
	Node* findMin(Node* current) const;
};

