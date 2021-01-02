//============================================================================
// Name        : unicode-reader.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
//#include <iterator>
#include <unordered_map>
#include <vector>

using namespace std;

long read_utf8(std::istreambuf_iterator<char> & iter) {
	unsigned char firstbyte = *iter;
	if ( iter == istreambuf_iterator<char>() )
		return -1;
	++iter;
	if ( (firstbyte & 0x80) == 0 )
		return firstbyte;
	long code = firstbyte;
	firstbyte <<= 1;
	while ( firstbyte & 0x80 ) {
		code <<= 8;
		code |= (unsigned char)(*iter);
		++iter;
		firstbyte <<= 1;
	}
	return code;
}

int main() {
	unordered_map<long, int> histg;
	cout << "utf-8 stats" << endl;

	ifstream inputf("./アウステルリッツの戦い - Wikipedia.html", ios::binary);

	for (istreambuf_iterator<char> iter = istreambuf_iterator<char>(inputf);
			iter != istreambuf_iterator<char>(); ){
		long code = read_utf8(iter);
		if (histg.count(code)) {
			histg[code] += 1;
		} else {
			histg[code] = 1;
		}
		//cout << std::hex << code << endl;
	}
	inputf.close();
	vector<pair<long, int> > codes(histg.cbegin(), histg.cend());
	sort(codes.begin(), codes.end());
	for(auto i = codes.begin(); i != codes.end(); ++i) {
		cout << std::hex << i->first << ": " << std::dec << i->second << endl;
	}
	return 0;
}
