//============================================================================
// Name        : NumberPlace_solver.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>

using namespace std;

void show_cells(const int rows, char cells[]);

int main(const int argc, const char * argv[]) {
	if ( argc < 3 ) {
		cerr << "give me an input in rows, '003 050 09... 090' format." << endl;
		return EXIT_FAILURE;
	}
	// count cells
	int rows = atoi(argv[1]);
	char cell[rows][rows];
	int cellnum = 0;
	const char * ptr;
	for(ptr = argv[2]; *ptr != '\0'; ++ptr) {
		if ( isdigit(*ptr) ) {
			cell[cellnum / rows][cellnum % rows] = *ptr - '0';
			cellnum += 1;
		}
	}
	if ( cellnum != rows*rows ) {
		cerr << cellnum << "digits!! give a sequence of exactly rows x rows digits!!" << endl;
		return EXIT_FAILURE;
	}

	show_cells(rows, cell);
	return 0;
}

void show_cells(const int rows, char *cell) {
	for(int r = 0; r < rows; ++r) {
		cout << "-";
		for(int c = 0; c < rows; ++c) {
			cout << "----";
		}
		cout << endl;
		cout << "|";
		for(int c = 0; c < rows; ++c) {
			if ( cell[r][c] == 0 )
				cout << " " << ' ' << " |";
			else
				cout << " " << (char) ('0'+cell[r][c]) << " |";
		}
		cout << endl;
		if (r+1 == rows) {
			cout << "-";
			for(int c = 0; c < rows; ++c) {
				cout << "----";
			}
			cout << endl;
		}
	}
}
