#include <iostream>
#include <string>
#include <fstream>

#include "person.h"
#include "utils.h"

Person::Person() {}
Person::Person(std::string name, long int id) : d_name(name), d_id(id) {}

std::string Person::name() {
	return d_name;
}

long int Person::id() {
	return d_id;
}

void Person::print() {
	std::cout << d_name << '\n';
	std::cout << d_id << '\n';
}

bool Person::operator< (const Person &p2){
	return this->d_id < p2.d_id ? true : false;
}

bool Person::operator== (const Person &p2){
	return this->d_id == p2.d_id ? true : false;
}

bool Person::operator> (const Person &p2){
	return this->d_id > p2.d_id ? true : false;
}

void Person::read(std::istream &fp){
	char buf[500];

	fp.getline(buf, 500, '\0');
	this->d_name.assign(buf);

	fp.read((char *) &this->d_id, sizeof(long int));
}

void Person::write(std::ostream &fp){
	std::string &str = this->d_name;
	long int &num = this->d_id;

	fp.write(str.c_str(), str.size()+1);
	fp.write((char *) &num, sizeof(long int));
}

Person Person::random(){
	std::string s;
	long int l;

	s = random_string();
	l = random_long();

	return Person(s, l);
}
