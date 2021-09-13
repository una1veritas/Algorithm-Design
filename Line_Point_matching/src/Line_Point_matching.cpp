//============================================================================
// Name        : Line_Point_matching.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int read_csv(istream & ifile, std::vector<vector<double> > &array) {
	std::istringstream strin;
	std::string buff;

	if ( !ifile ) {
		fprintf(stderr, "file open failed.\n");
		return 0; // failed
	}
	while (! ifile.eof()) {
		double x;
		getline(ifile, buff, '\n');
		strin.str(buff);
		strin.clear();
		while ( !strin.eof() ) {
			strin >> x;
			std::cout << x << ", ";
			std::cout.flush();
		}
		std::cout << std::endl;
	}
	return 1; // succeeded
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	ifstream ifile("test.csv");
	vector<vector<double>> v;
	read_csv(ifile, v);
	ifile.close();
	return 0;
}
