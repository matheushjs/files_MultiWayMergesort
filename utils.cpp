#include <string>
#include <random>

#include "utils.h"

using namespace std;

string random_string(){
	static random_device r;
	static default_random_engine eng(r());
	static uniform_int_distribution<int> runif_size(1, 50);
	static uniform_int_distribution<char> runif_char(65, 90);

	int i, size;
	string str;

	size = runif_size(eng);

	for(i = 0; i < size; i++){
		str.push_back(runif_char(eng));
	}

	return str;
}

long int random_long(){
	static random_device r;
	static default_random_engine eng(r());
	static uniform_int_distribution<long int> runif;

	return runif(eng);
}
