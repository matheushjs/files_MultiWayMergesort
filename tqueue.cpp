#include "tqueue.h"

TQueue::TQueue(std::istream &srcfile, int offset, int nRecords)
	: d_file(srcfile), d_offset(offset),
	  d_nRecords(nRecords), d_nRead(0)
{
}

bool TQueue::empty(){
	return d_nRead == d_nRecords ? true : false;
}

Person TQueue::next(){
	// TODO: Buffering of Person objects

	if(empty()){
		return Person("", -1); // Not going to throw any exception
	} else {
		Person p;
		d_file.seekg(d_offset);
		p.read(d_file);
		return p;
	}
}
