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

void show_cells(const int rows, const int * cells);
int read_input(const int argc, const char * argv[], int * & cells);

const static int rows = 9;
int main(const int argc, const char * argv[]) {

	int * cells = NULL;
	if ( read_input(argc, argv, cells) )
		return EXIT_FAILURE;
	show_cells(rows, cells);

	int ans[rows*rows];
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < rows; ++c) {
				ans[r*rows+c] = 1 + c;
		}
		for(int c = 0; c < rows; ++c) {
			if ( cells[r*rows+c] != 0 )
				ans[r*rows+cells[r*rows+c]-1] = 0; //rows + 1;
		}
		sort(ans+(r*rows), ans+(r*rows+rows));
		for(int c = 0; c < rows; ++c) {
			if ( ans[r*rows+c] == 0 )
				ans[r*rows+c] = rows+1;
		}
	}

	while (next_permutation(ans, ans+rows)) {
		show_cells(rows, (const int *) ans);
		cout << endl;
	}
	delete [] cells;
	return 0;
}

int read_input(const int argc, const char * argv[], int * & cells) {
	if ( argc <= 81 ) {
		cerr << "give me an input in '0 0 3 0 5 0 0 9 ... 0 9 0' format." << endl;
		return EXIT_FAILURE;
	}
	cells = new int[rows*rows];
	int cellnum = 0;
	for(int i = 1; i < argc && cellnum <= 81; ++i) {
		cells[cellnum] = atoi(argv[i]);
		cellnum += 1;
	}
	if ( cellnum != rows*rows ) {
		cerr << cellnum << "digits!! give a sequence of exact rows x rows numbers!!" << endl;
		return EXIT_FAILURE;
	}
	return 0;
}

void show_cells(const int rows, const int * cells) {
	for(int r = 0; r < rows; ++r) {
		cout << "+";
		for(int c = 0; c < rows; ++c) {
			cout << "---+";
		}
		cout << endl;
		cout << "|";
		for(int c = 0; c < rows; ++c) {
			if ( cells[r*rows + c] == 0 )
				cout << " " << ' ' << " |";
			else
				cout << " " << (char) ('0'+cells[r*rows + c]) << " |";
		}
		cout << endl;
		if (r+1 == rows) {
			cout << "+";
			for(int c = 0; c < rows; ++c) {
				cout << "---+";
			}
			cout << endl;
		}
	}
}
