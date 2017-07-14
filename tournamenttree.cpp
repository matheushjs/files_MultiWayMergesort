#include "tournamenttree.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define PARENT(X) ((X-1)/2)
#define LEFT(X) (X*2+1)
#define RIGHT(X) (X*2+2)

// Index of first node in level X of the heap-like tree.
// Level is given as a number >= 1
#define LEVELIDX(X) (pow(2,X-1) - 1)

// Number of nodes in a given X level of the heap-like tree.
#define LEVELCOUNT(X) (pow(2, X-1))

static
void heapify_up(vector<Person> &vec, int index){
	while(index != 0) {
		if(vec[PARENT(index)] < vec[index]){
			swap(vec[PARENT(index)], vec[index]);
			index = PARENT(index);
		} else break;
	}
}

static
void heapify_down(vector<Person> &vec, int index, int size){
	int largest, left, right;

	while(true){
		left = LEFT(index);
		right = RIGHT(index);
		largest = index;

		if(left < size && vec[left] > vec[largest])
			largest = left;

		if(right < size && vec[right] > vec[largest])
			largest = right;

		if(largest != index){
			swap(vec[index], vec[largest]);
			index = largest;
		} else break;
	}
}

static
void sortPerson(vector<Person> &vec){
	for(int i = 0, n = vec.size(); i < n; i++)
		heapify_up(vec, i);

	for(int i = vec.size()-1; i > 0; i--){
		swap(vec[0], vec[i]);
		heapify_down(vec, 0, i);
	}
}

static
int nextpow2(int num){
	int i = 1;
	while(i < num)
		i <<= 1;
	return i;
}

TournamentTree::TournamentTree(istream &srcfile, int initOffset, int nRecords, int nLeaves)
	: d_infile(srcfile),
	  d_treeHeight( (int) log2(nextpow2(nLeaves)) + 1 ),
	  d_treeSize( pow(2, d_treeHeight) - 1), // heap-style tree
	  d_tree( d_treeSize ),
	  d_initOffset(initOffset), d_nRecords(nRecords),
	  d_nLeaves(nLeaves), d_nRemoved(0)
{
	d_outfile.open("blocks.db", ios::in | ios::out | ios::trunc);

	// Number of records per block that will be sorted in memory
	int blockSize = nRecords / nLeaves; // Let it round down

	d_infile.seekg(d_initOffset, ios::beg);

	int curOffset;
	Person p;
	vector<Person> vec;
	for(int i = 0; i < d_nLeaves; i++){
		vec.clear();
		curOffset = d_infile.tellg();

		// Read blockSize Person objects from the file
		for(int j = 0; j < blockSize; j++){
			p.read(d_infile);
			vec.push_back(p);
		}

		// If it's last leaf, read all Person until the end of the file
		if(i == d_nLeaves - 1){
			while(true){
				p.read(d_infile);
				if(!d_infile.good()){
					d_infile.clear();
					break;
				}
				vec.push_back(p);
			}
		}

		sortPerson(vec);

		// Save sorted block to the sorted file
		d_outfile.clear();
		d_outfile.seekp(0, ios::end);
		for(Person &pp: vec){
			pp.write(d_outfile);
		}

		// Create a TQueue for this block of the file and add it to d_leaves
		d_leaves.push_back( TQueue(d_outfile, curOffset - d_initOffset, vec.size()) );
	}

	buildTree();
}

// Recursively fills a tournament tree, based on the leaf nodes.
// Each node receives the minimum between its children.
static
void fillTree(vector<long int> &vec, int idx, int size){
	if(idx >= size) return;

	int right = RIGHT(idx);
	int left = LEFT(idx);

	fillTree(vec, right, size);
	fillTree(vec, left, size);

	if(right < size) {
		vec[idx] = min(vec[left], vec[right]);
	} else if (left < size) {
		vec[idx] = vec[left];
	}
}

void TournamentTree::buildTree(){
	int idx, nLeaves;

	// Get the first index of the last level of the tree
	idx = LEVELIDX(d_treeHeight);

	// Get the number of leaves in that last level
	nLeaves = LEVELCOUNT(d_treeHeight);

	// Fill the last level with data from the queues
	for(int i = 0; i < nLeaves; i++){
		if(i < d_nLeaves){
			d_tree[idx+i] = d_leaves[i].peek().id();
		} else {
			d_tree[idx+i] = INT64_MAX; // Empty leaves
		}
	}

	fillTree(d_tree, 0, d_treeSize);
}

void TournamentTree::printTree(){
	// Print heap (DEBUGGING)
	int count = 0;
	for(int i = 0; i < d_treeHeight; i++){
		for(int j = pow(2, i); j > 0; j--){
			cout << (d_tree[count] == INT64_MAX ? -1 : d_tree[count]) << ' ';
			count++;
		}
		cout << '\n';
	}
}

bool TournamentTree::empty() {
	return d_nRemoved == d_nRecords ? true : false;
}

void TournamentTree::rebuildTree(int idx, long int value){
	int left, right;

	d_tree[idx] = value;

	do {
		idx = PARENT(idx);
		right = RIGHT(idx);
		left = LEFT(idx);

		d_tree[idx] = min(d_tree[right], d_tree[left]);
	} while(idx != 0);
}

Person TournamentTree::next(){
	int curIdx = 0;
	int idxLim = LEVELIDX(d_treeHeight); //Index of first leaf node.

	// Follow the path whose elements are all equal the element in the root
	while(curIdx < idxLim){
		int left = LEFT(curIdx);
		int right = RIGHT(curIdx);

		if(d_tree[left] == d_tree[curIdx]){
			curIdx = left;
		} else {
			curIdx = right;
		}
	}

	int tqueue_number = curIdx - idxLim;
	Person p = d_leaves[tqueue_number].next();

	rebuildTree(curIdx, d_leaves[tqueue_number].peek().id());
	d_nRemoved++;

	return p;
}
