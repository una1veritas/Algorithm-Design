//============================================================================
// Name        : StringConverter.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

string reversed6(const string & s) {
	string t;
	for (int i = 0; i < s.size() and i < 6;++i)
		t += s[s.size() - 1 - i];
	return t;
}

int main(int argc, char * argv[]) {
	string id(argv[1]);
	id = reversed6(id);
	id[0] += 17;
	cout << id << endl;
	return 0;
}
