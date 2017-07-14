#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H

#include <vector>
#include <fstream>

#include "tqueue.h"
#include "person.h"

/* Class that implements a Tournament tree.
 * The tree is used to manage the values in the leaf nodes. Each non-leaf node contains the minimal
 *   value among its children. This way, the root node always has the minimal value among all leaf nodes.
 */
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

	// Number of Person objects removed from the tree.
	int d_nRemoved;

	// Builds the heap-like tree based on the vector of TQueues
	void buildTree();

	// Rebuilds the heap-like tree with the new value added at a leaf node
	void rebuildTree(int idx, long int value);

	void printTree();

public:
	TournamentTree(std::istream &srcfile, int initOffset, int nRecords, int nLeaves);

	// Returns whether all records have been removed from the tree or not.
	bool empty();

	// Returns the next Person object in the tree.
	// Minimum Person comes first.
	Person next();
};

#endif // TOURNAMENTTREE_H
