#include <iostream>
#include "tqueue.h"

using namespace std;

TQueue::TQueue(istream &srcfile, int offset, int nRecords)
	: d_file(srcfile), d_offset(offset),
	  d_nRecords(nRecords), d_nRead(0)
{
	readNext();
}

bool TQueue::empty(){
	return d_onHold == 0 ? true : false;
}

bool TQueue::allRead(){
	return d_nRead == d_nRecords ? true : false;
}

void TQueue::readNext(){
	if(!allRead()) {
		d_file.seekg(d_offset, ios::beg);
		d_person.read(d_file);
		d_onHold = 1;
		d_offset = d_file.tellg();
	}
}

Person TQueue::next(){
	Person p = std::move(d_person);
	d_onHold = 0;

	readNext();

	return p;
}

Person &TQueue::peek(){
	return d_person;
}
