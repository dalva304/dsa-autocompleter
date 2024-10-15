//Diana Alvarez Sanchez

#include <iostream>
#include "autocompleter.h"

using namespace std;

// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
Autocompleter::Autocompleter() {
	root = nullptr;
}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(log(n)) time.
void Autocompleter::insert(string x, int freq) {
	Entry A; 
	A.s = x;
	A.freq = freq;
	insert_recurse(A, root);
}

// Returns the number of strings in the dictionary
// of possible completions.
//
// Must run in O(n) time.
int Autocompleter::size() {
	return size_recurse(root);
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run fast.  In particular, you should not search all nodes in the
// tree for possible completions.
// Instead, only search regions of the tree for which a completion could
// be present, which will yield a run time bound of O(k log n ) time,
// where k is the number of completions in the tree.
void Autocompleter::completions(string x, vector<string>& T) {
	T.clear(); //emptying out for the three
	vector<Entry>A;
	completions_recurse(x, root, A); //doing so recursively

	for (int i = 0; i < A.size(); i++) {
		T.push_back(A[i].s);
	}

}


// Returns the size of the binary tree rooted at p.
	//
	// Should run in O(n) time.
int Autocompleter::size_recurse(Node* p) {
	if (p == nullptr) //if nothing
		return 0;
	else
		return 1 + size_recurse(p->left) + size_recurse(p->right);
	// 1 + count from left + count from right
}

// Fills C with the completions of x in the BST rooted at p.
void Autocompleter::completions_recurse(string x, Node* p, vector<Entry>& C) {
	if (p == nullptr) //if none. do nothing
		return;
	else {
		int set = x.size();
		string current = p->e.s;
		current.resize(set);
		if (x == current) {
			C.push_back(p->e);
			//where k is the number of completions
			for (int i = C.size() - 1; i > 0; i--) { 
				if (C[i].freq >= C[i - 1].freq) {
					swap(C[i], C[i - 1]);
				}
				else {
					break;
				}
			}
			if (C.size() > 3) { // if greater than 3 adjust items
				C.pop_back();
			}
			completions_recurse(x, p->left, C);
			completions_recurse(x, p->right, C);
		}
		else {
			if (x < p->e.s) {
				completions_recurse(x, p->left, C);
			}
			if (x > p->e.s) {
				completions_recurse(x, p->right, C);
			}
		}
	}
}

// Inserts an Entry into an AVL tree rooted at p.
//
// Should run in O(log(n)) time.
void Autocompleter::insert_recurse(Entry e, Node*& p) {
	// if nothing in the tree or if the pointer matches
	if (p == nullptr || e.s == p->e.s) {
		p = new Node(e); //insert the ndoe
	}
	else if(e.s < p->e.s){
		// if less
		insert_recurse(e, p->left); //insert to left of tree
	}
	else {
		insert_recurse(e, p->right); //insert to the right
	}
	update_height(p);
	rebalance(p);
}

// Rebalances the AVL tree rooted at p.
// Helpful for insert().
// Should be called on every node visited during
// the search in reverse search order.
//
// Should run in O(1) time.
void Autocompleter::rebalance(Node*& p) {
	if (height(p->right) - height(p->left) >= 2) { //if unbalanced by 2 or more !
		if (height(p->right->right) >= height(p->right->left)){//if the height is greater on the right
			left_rotate(p);
		}
		else {
			right_rotate(p->right);
			left_rotate(p);
		}
	}
	else if (height(p->left) - height(p->right) >= 2) { //if unbalanced
		if (height(p->left->left) > height(p->left->right)) { // left is greater than right
			right_rotate(p);
		}
		else {
			left_rotate(p->left);
			right_rotate(p);
		}
	}
	else {
		return;
	}
}

// Perform left and right rotations
// of an AVL tree rooted at p (helpful for implementing rebalance).
//
// Should run in O(1) time.
//did in class !!
void Autocompleter::right_rotate(Node*& p) {
	Node* A = p;
	Node* B = p->left;
	Node* bR = B->right;

	p = B;
	B->right = A;
	A->left = bR;

	update_height(A);
	update_height(B);
}
void Autocompleter::left_rotate(Node*& p) {
	Node* A = p;
	Node* B = A->right;
	Node* bL = B->left;

	p = B;
	B->left = A;
	A->right = bL;

	update_height(A);
	update_height(B);

}