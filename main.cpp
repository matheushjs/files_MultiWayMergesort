#include <iostream>
#include <chrono>

#include "mydatabase.h"

using namespace std;

int main() {
	MyDatabase db;

	chrono::time_point<chrono::system_clock> begt, endt;

	begt = chrono::system_clock::now();
	db.mergeSort(200);
	endt = chrono::system_clock::now();
	cout << "Time: " << chrono::duration<double>(endt-begt).count() << '\n';

	return 0;
}
