//============================================================================
// Name        : binaryfile_io.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cinttypes>
#include <cstring>

#include <sys/stat.h>

using namespace std;

struct datafileinfo {
	static constexpr uint32_t garbages_max = 61;
	static constexpr uint32_t info_pos = 0;

	uint32_t capacity;
	uint32_t size;
	uint32_t garbages[garbages_max+1];
};

int main(int argc, char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	//datafileinfo header;

	constexpr unsigned int buffer_size = 256;
	cout << sizeof(datafileinfo) << endl;
	char buffer[buffer_size];
	char text[buffer_size] = "This is a pen, this is an apple, an apple pen.";
	/*
	if ( bfile.read(buffer, buffer_size) ) {
	    memcpy((void *) &header, (const void *) buffer, sizeof(datafileinfo));
	    cout << "read." << endl;
	} else if ( bfile.gcount() < buffer_size ) {
		header.capacity = 0;
		header.size = 0;
		header.garbages[0] = 0;
			*/

	if (argc > 1) {
		strcpy(text, argv[1]);
	}
	string datafilename = "data.bin";
	struct stat test;
	if ( stat(datafilename.c_str(), &test) != 0 ) {
		cout << "Cannot open file..." << flush;
		std::ofstream tfile(datafilename, ios::binary | ios::out );
		tfile.close();
		cout << " created." << endl;
	}

	std::fstream bfile;
	bfile.open("data.bin", ios::binary | ios::out | ios::in );

	memset(buffer, 0, buffer_size);
	//memcpy((void *) buffer, (const void *) &header, sizeof(datafileinfo));
	// bfile.clear();
	bfile.seekp(0);
	bfile.write(text, buffer_size);
	bfile.close();
	cout << "written." << endl;
		/*
    } else {
    	cout << "unknown status." << endl;
    	return EXIT_FAILURE;
	}
	*/
	/*
		bfile.seekg (0);
	    bfile.read (buffer, buffer_size);
	    cout << bfile.gcount() << endl;
	    cout << "read. " << buffer << endl;

		bfile.close();
		*/
	return EXIT_SUCCESS;
}
