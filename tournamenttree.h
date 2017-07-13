#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H

#include <vector>
#include <fstream>

#include "tqueue.h"
#include "person.h"

class TournamentTree {
	std::istream &d_infile;
	std::fstream d_outfile;
	std::vector<TQueue> d_leaves;

	int d_treeHeight;
	int d_treeSize;
	std::vector<long int> d_tree;

	// Offset after the file header.
	int d_initOffset;

	// Number of records in the file.
	int d_nRecords;

	// Number of leaf nodes in the tournament tree.
	int d_nLeaves;

	// Builds the heap-like tree based on the vector of TQueues
	void buildTree();

public:
	TournamentTree(std::istream &srcfile, int initOffset, int nRecords, int nLeaves);
};

#endif // TOURNAMENTTREE_H
