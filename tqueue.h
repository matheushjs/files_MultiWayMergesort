#ifndef TQUEUE_H
#define TQUEUE_H

#include <fstream>
#include "person.h"

class TQueue {
	// Associated ifstream
	std::istream &d_file;

	// Offset of next Person that can be read.
	int d_offset;

	// Number of records that this Queue can read.
	int d_nRecords;

	// Number of records read so far.
	int d_nRead;

public:
	TQueue(std::istream &srcfile, int offset, int nRecords);
	bool empty();
	Person next();
};

#endif // TQUEUE_H
