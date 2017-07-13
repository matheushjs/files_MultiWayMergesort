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

public:
	MyDatabase();
	~MyDatabase();

	int size();

	// Prints all records in the database file.
	void printAll();

	// Generates a random database file, with nRecords records.
	void generateRandomFile(long int nRecords);

	// Sorts the file using external mergesort
	void mergeSort(int nLeaves);
};

#endif // MYDATABASE_H
