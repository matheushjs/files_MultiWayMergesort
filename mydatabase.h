#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <fstream>
#include <string>

#include "person.h"

class MyDatabase {
	std::fstream d_fp;
	std::string d_filename;

	// Number of elements in the database
	int d_size;

	// Reads next person in the database file.
	Person readPerson();

	// Writes a person to the database file.
	void writePerson(Person &p);

public:
	MyDatabase();

	int size();

	// The database file is a sequence of ID (long int) / name (string).
	// The input file 'fp' should be a sequence of ID (a string representing a number) and
	//   a name, separated by blank spaces.
	void readFromInputFile(std::istream &fp);

	// Prints all records in the database file.
	void printAll();

	void generateRandomFile(long int nRecords);
};

#endif // MYDATABASE_H
