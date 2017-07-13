#include "tournamenttree.h"

#include <fstream>
#include <cmath>

using namespace std;

TournamentTree::TournamentTree(istream &srcfile, int initOffset, int nRecords, int nLeaves)
	: d_infile(srcfile),
	  d_vecSize( pow(2, ceil(log2(nLeaves)) + 1) - 1), // heap-style tree
	  d_vector( d_vecSize ),
	  d_initOffset(initOffset), d_nRecords(nRecords),
	  d_nLeaves(nLeaves)
{
	d_outfile.open("output.db", ios::out | ios::trunc);

	int blockSize; // Number of records per block that will be sorted in memory
	blockSize = nRecords / nLeaves; // Let it round down

	for(int i = 0; i < d_nLeaves; i++){
		// Read nRecords into a vector
		// Store the ftell() after all records are read, in a variable TELL
		// Sort the vector using any method
		// Write the vector back to the file
		// Create a TQueue for this block of the file and add it to d_leaves
	}
}
