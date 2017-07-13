#ifndef TQUEUE_H
#define TQUEUE_H

#include <fstream>
#include <queue>
#include "person.h"

class TQueue {
	// Max number of Person objects in the queue
	const static int BUFSIZE = 65;

	// Associated ifstream
	std::istream &d_file;

	// Offset of next Person that can be read.
	int d_offset;

	// Number of records that this Queue can read.
	int d_nRecords;

	// Number of records read so far.
	int d_nRead;

	// Next person on the queue
	std::queue<Person> d_queue;

	// Retrieves the next Person objects from the file
	void readNext();

	// Returns True if all records have been read from the file.
	// Some records might still be in memory; this can be checked with d_queue.
	bool allRead();

public:
	TQueue(std::istream &srcfile, int offset, int nRecords);

	// Returns True if there are no more Person objects in this queue.
	bool empty();

	// Returns the next Person, and removes it from the queue.
	Person next();

	// Returns the next Person, but does not remove it from the queue.
	Person &peek();
};

#endif // TQUEUE_H
