#include <iostream>
#include <vector>
#include <thread>

#include "mydatabase.h"
#include "person.h"

using namespace std;

MyDatabase::MyDatabase() : d_filename("database.db") {
	d_fp.open(d_filename, d_fp.out | d_fp.in);

	if(!d_fp.is_open()){
		cout << "Creating new file.\n";
		d_fp.open(d_filename, d_fp.in | d_fp.out | d_fp.trunc);
	}

	d_size = 0;
	Person p;
	while(true){
		p.read(d_fp);
		if(d_fp.eof()) break;
		d_size++;
	}

	d_fp.clear();
}

int MyDatabase::size(){
	return d_size;
}

Person MyDatabase::readPerson(){
	Person p;
	p.read(d_fp);
	return p;
}

void MyDatabase::writePerson(Person &p){
	p.write(d_fp);
}


void MyDatabase::readFromInputFile(istream &fp){
	string str;
	long int num;

	d_fp.clear();
	d_fp.seekp(0, d_fp.end);
	do {
		if(fp >> num && fp >> str){
			d_fp.write(str.c_str(), str.size()+1);
			d_fp.write((char *) &num, sizeof(long int));
		}
	} while(!fp.eof());
	d_fp.flush();
}

void MyDatabase::printAll(){
	Person p;

	d_fp.clear();
	d_fp.seekg(0, d_fp.beg);

	do {
		p = readPerson();

		if(!d_fp.eof()) p.print();
		else break;

	} while(true);
}

void MyDatabase::generateRandomFile(long nRecords){
	d_fp.close();
	d_fp.open(d_filename, ios::in | ios::out | ios::trunc);

	long count;
	for(count = 0; count < nRecords; count++){
		Person::random().write(d_fp);
	}
}
