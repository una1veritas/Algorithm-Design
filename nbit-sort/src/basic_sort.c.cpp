/*
 * basic_sort.cpp
 *
 * Basic quadratic time sort by Sin
 * The input array of floating numbers is read only,
 * as working space, only n bits are allowed.
 *
 */

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

template <typename T>
struct output{
	T * _stream;
	unsigned int _lastindex;
	unsigned int _size;

	output() {
		_size = 16;
		_lastindex = 0;
		_stream = new T[_size];
	}

	~output() {
		delete [] _stream;
	}

	void write(const T data) {
		_stream[_lastindex++] = data;
	}

	friend std::ostream & operator<<(std::ostream & outs, const output & oput) {
		for(unsigned int i = 0; i < oput._lastindex; ++i)
			outs << oput._stream[i] << " ";
		return outs;
	}
};

int main(const int argc, const char * argv[]) {
	printf("Hi.\n");

	const int n = argc - 1;
	double array[n];
	const char ** handle = argv+1;
	for(int i = 0; i < n; ++i) {
		array[i] = strtod(*handle++, NULL);
	}
	const double * data = array;
	printf("in data:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d: %f\n", i, data[i]);
	}
	printf("\n");

	// read/write working space
	bool boolarray[n];
	int tmax_index;
	// write-only output
	output<double> out;

	// working space initialization
	for(int i = 0; i < n; ++i)
		boolarray[i] = false;

	for(int i = 0; i < n; ++i) {
		tmax_index = 0;
		for(int j = 0; j < n; ++j) {
			if ( boolarray[tmax_index] ||
					( !boolarray[j] && data[tmax_index] > data[j]) ) {
				tmax_index = j;
			}
		}
		boolarray[tmax_index] = true;
		for(int i = 0; i < n; ++i) {
			printf("%d",boolarray[i]);
		}
		printf("\n");
		out.write(data[tmax_index]);
	}

	printf("output:\n");
	std::cout << out << std::endl;

	return EXIT_SUCCESS;
}
