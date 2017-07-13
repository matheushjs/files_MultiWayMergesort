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
	return d_queue.size() == 0 ? true : false;
}

bool TQueue::allRead(){
	return d_nRead == d_nRecords ? true : false;
}

void TQueue::readNext(){
	Person p;

	if(!allRead())
		d_file.seekg(d_offset, ios::beg);

	int i;
	for(i = 0; i < TQueue::BUFSIZE && !allRead(); i++){
		p.read(d_file);
		d_queue.push(move(p));

		d_nRead++;
	}

	if(i > 0)
		d_offset = d_file.tellg();
}

Person TQueue::next(){
	Person p = move(d_queue.front());
	d_queue.pop();

	readNext();

	return p;
}

Person &TQueue::peek(){
	return d_queue.front();
}
