#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(const int argc, char *argv[]) {

	if (argc < 3) {
		cout << "Give two strings as arguments." << endl;
		return EXIT_FAILURE;
	}

	string text(argv[1]), pattern(argv[2]);

	int i, j;
	int edist[text.size()+1][pattern.size()+1];

	for (i = 0; i <= text.size(); i++)
		edist[i][0] = i;
	for (j = 0; j <= pattern.size(); j++)
		edist[0][j] = j;

	for (i = 1; i <= text.size(); i++) {
		for (j = 1; j <= pattern.size(); j++) {
			int t = edist[i - 1][j - 1];
			if (text[i - 1] != pattern[j - 1])
				t += 1;
			if (edist[i - 1][j] + 1 < t)
				t = edist[i - 1][j] + 1;
			if (edist[i][j - 1] + 1 < t)
				t = edist[i][j - 1] + 1;
			edist[i][j] = t;
		}
	}

	cout << std::setw(6) << " ";
	for (i = 0; i < pattern.size(); i++) {
		cout << std::setw(3) << pattern[i];
	}
	cout << endl;
	for (i = 0; i <= text.size(); i++) {
		if (i == 0) {
			cout << std::setw(3) << " ";
		} else {
			cout << std::setw(3) << text[i-1];
		}
		for (j = 0; j <= pattern.size(); j++) {
			cout << std::setw(3) << edist[i][j];
		}
		cout << endl;
	}

	cout << endl << std::endl << "Result: "
			<< edist[text.size()][pattern.size()] << endl;

	return EXIT_SUCCESS;
}
