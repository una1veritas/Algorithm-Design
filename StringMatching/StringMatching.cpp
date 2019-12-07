#include <iostream>
#include <string>
#include <vector>


class kmp {
	std::string pattern;
	std::vector<int> failure;
	int state;

private:
	void initialize_failure() {
		int i, j;
		i = 1, j = 0, failure[0] = 0;
		while ( i < pattern.size() ) {
			if (pattern[i] == pattern[j]) {
				failure[i] = j + 1;
				j++;
				i++;
			} else {
				if (j > 0) {
					j = failure[j - 1];
				} else {
					i++;
				}
			}
		}
	}

public:
	kmp(const char * str) : pattern(str), state(0) {
		failure.resize(pattern.size());
		initialize_failure();
	}

	int search(std::string txt) {
		int pos = 0;
		state = 0;
		while (pos < txt.size()) {
			std::cout << pos << ", " << state << std::endl;
			if ( txt[pos] == pattern[state]) {
				state++;
				pos++;
				if (state == pattern.size()) {
					std::cout << "matched. " << pos << ", " << state << std::endl;
					return pos - pattern.size();
				}
			} else {
				if (state != 0) {
					state = failure[state-1];
					std::cout << "failured " << state << std::endl;
				}
			}
		}
		return pos;
	}

	friend std::ostream & operator<<(std::ostream & ost, const kmp & p) {
		ost << "kmp('" << p.pattern << "' (" << p.pattern.size() << ") [";
		for(int i = 0; i < p.failure.size(); i++) {
			ost << p.failure[i];
			if ( i+1 < p.failure.size() )
				ost << ", ";
		}
		ost << "]) ";
		return ost;
	}
};

int main(int argc, char **argv) {
	kmp p("aabbaabbcc");
	std::string text("aabaabbaabbaabbccaabb");

	std::cout << p << std::endl;
	std::cout << text << " (" << text.size() << ")" << std::endl;
	std::cout << "search: " << std::endl << p.search(text) << std::endl;

	return 0;
}
