#include "tqueue.h"

TQueue::TQueue(std::istream &srcfile, int offset, int nRecords)
	: d_file(srcfile), d_offset(offset),
	  d_nRecords(nRecords), d_nRead(0)
{
	readNext();
}

bool TQueue::empty(){
	return d_nRead == d_nRecords ? true : false;
}

void TQueue::readNext(){
	if(!empty()) {
		d_file.seekg(d_offset);
		d_person.read(d_file);
		d_offset = d_file.tellg();
	}
}

Person TQueue::next(){
	Person p = std::move(d_person);

	readNext();

	return p;
}

Person &TQueue::peek(){
	return d_person;
}
