#include "tournamenttree.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define PARENT(X) ((X-1)/2)
#define LEFT(X) (X*2+1)
#define RIGHT(X) (X*2+2)

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

TournamentTree::TournamentTree(istream &srcfile, int initOffset, int nRecords, int nLeaves)
	: d_infile(srcfile),
	  d_vecSize( pow(2, ceil(log2(nLeaves)) + 1) - 1), // heap-style tree
	  d_vector( d_vecSize ),
	  d_initOffset(initOffset), d_nRecords(nRecords),
	  d_nLeaves(nLeaves)
{
	d_outfile.open("blocks.db", ios::in | ios::out | ios::trunc);

	int blockSize; // Number of records per block that will be sorted in memory
	blockSize = nRecords / nLeaves; // Let it round down

	d_infile.seekg(d_initOffset);

	Person p;
	vector<Person> vec;
	for(int i = 0; i < d_nLeaves; i++){
		vec.clear();

		// Read blockSize Person from the file
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
		for(Person &pp: vec){
			pp.write(d_outfile);
			cout << pp.id() << '\n';
		}

		// Create a TQueue for this block of the file and add it to d_leaves
		d_leaves.push_back( TQueue(d_outfile, d_infile.tellg() - (long) d_initOffset, vec.size()) );
	}

	// INITIALIZE TREE HERE
}
