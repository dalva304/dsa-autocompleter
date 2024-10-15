//Diana Alvarez Sanchez
//10-13-2024
#include "autocompleter.h"

// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter() {
	//creating a new root node. starting count from0
	root = new Node();
	count = 0;
}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(1) time.
void Autocompleter::insert(string x, int freq) {
	//new node pointer temp
	Node* ptemp = root;

	//new entry
	Entry e;
	e.s = x;
	e.freq = freq;

	//for each letter in string
	for (int i = 0; i < x.size(); i++) {
		//if char doesnt exist
		if (ptemp->children[x[i]] == nullptr)
			ptemp->children[x[i]] = new Node();

		//update top node
		Entry topT = e;

		//update vector
		for (int j = 0; j < 3 && j < ptemp->top.size();   j++) {
			if (ptemp->top[j].freq < topT.freq) {
				//swap
				Entry eTemp = ptemp->top[j];
				ptemp->top[j] = topT;
				topT = eTemp;
			}
		}
		//updated top, or still room
		if (ptemp->top.size() < 3)
			ptemp->top.push_back(topT);

		ptemp = ptemp->children[x[i]];


		Entry topT = e;

		//update top three 
		for (int j = 0; j < 3 && j < ptemp->top.size(); j++) {
			if (ptemp->top[j].freq < topT.freq) {
				Entry etemp = ptemp->top[j];
				ptemp->top[j] = topT;
				topT = etemp;
			}
		}
		if (ptemp->top.size() < 3) {
			ptemp->top.push_back(topT);
		}
		ptemp->marked = true;

		//oncrease count
		count++;
	}


}

// Returns the number of strings in the dictionary.
// 
// Must run in O(1) time.
int Autocompleter::size() {
	return count;
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then 
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
// 
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string>& T) {
	//staart at root
	Node* ptemp = root;
	
	//clear out to bring in
	T.clear();

	//go through trie
	for (int i = 0; i < x.size(); i++) {
		if (ptemp->children[x[i]] == nullptr)return;
		ptemp = ptemp->children[x[i]];
	}

	for (int i = 0; i < 3 && i < ptemp->top.size(); i++)
		T.push_back(ptemp->top[i].s);
}