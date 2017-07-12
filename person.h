#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <fstream>

class Person {
	std::string d_name;
	long int d_id;

public:
	Person();
	Person(std::string name, long int id);

	std::string name();
	long int id();
	void print();

	void read(std::istream &fp);
	void write(std::ostream &fp);

	bool operator< (const Person &p2);
	bool operator== (const Person &p2);
	bool operator> (const Person &p2);

	static Person random();
};

#endif // PERSON
