#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char **argv) {
	std::vector<int> varray;
	std::stringstream argstream;
	if ( argc > 1 ) {
		argstream.str(argv[1]);
		//argstream.clear();
	}

	std::cout << argstream.str() << std::endl;
	int val;
	int ch;
	while ( argstream ) {
		ch = (char)argstream.peek();
		if ( std::isdigit(ch) || ch == '-' || ch == '+' ) {
			argstream >> val;
			varray.push_back(val);
		} else {
			argstream.ignore(1);
		}
	}

	for(auto i = varray.begin(); i != varray.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << std::endl;
	return 0;
}
