#include <iostream>
#include <vector>

#include "mydatabase.h"
#include "person.h"
#include "tournamenttree.h"

using namespace std;

MyDatabase::MyDatabase() : d_filename("database.db") {
	d_fp.open(d_filename, d_fp.out | d_fp.in);

	if(!d_fp.is_open()){
		cout << "Creating new file.\n";
		d_fp.open(d_filename, d_fp.in | d_fp.out | d_fp.trunc);

		// Write header
		d_size = 0;
		d_fp.write( (char*) &d_size, sizeof(int));
	} else {
		d_fp.read( (char*) &d_size, sizeof(int));
	}
}

MyDatabase::~MyDatabase() {
	d_fp.clear();
	d_fp.seekp(0, ios::beg);
	d_fp.write( (char*) &d_size, sizeof(int));
}

int MyDatabase::size(){
	return d_size;
}

void MyDatabase::printAll(){
	Person p;

	d_fp.clear();
	d_fp.seekg(sizeof(int), d_fp.beg);

	do {
		p.read(d_fp);

		if(!d_fp.eof()) p.print();
		else break;

	} while(true);
}

void MyDatabase::generateRandomFile(long nRecords){
	d_fp.close();
	d_fp.open(d_filename, ios::in | ios::out | ios::trunc);

	d_size = nRecords;
	d_fp.write( (char*) &d_size, sizeof(int));

	long count;
	for(count = 0; count < nRecords; count++){
		Person::random().write(d_fp);
	}
}

void MyDatabase::mergeSort(int nLeaves){
	TournamentTree tree(d_fp, sizeof(int), d_size, nLeaves);
	ofstream file;

	file.open("output.db", ios::out | ios::trunc);

	int count = 0;
	while(!tree.empty()){
		tree.next().write(file);
		//Person p = tree.next();
		//cout << p.id() << '\n';
		count++;
	}

	d_fp.flush();
}
