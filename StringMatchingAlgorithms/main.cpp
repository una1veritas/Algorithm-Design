#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class kmp {
	std::string pattern;
	std::vector<int> failure;
	int state;

private:
	void initialize() {
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
		initialize();
	}

	int find(const std::string & txt) {
		int pos = 0;
		state = 0;
		while (pos < txt.size() - pattern.size() + 1) {
			//std::cout << pos << ", " << state << std::endl;
			if ( txt[pos] == pattern[state]) {
				++state;
				++pos;
				if (state == pattern.size()) {
					//std::cout << "matched. " << pos << ", " << state << std::endl;
					return pos - pattern.size();
				}
			} else {
				if ( state == 0 ) {
					++pos;
				} else {
					state = failure[state-1];
					//std::cout << "failed: " << pos << ", " << state << std::endl;
				}
			}
		}
		return pos;
	}

	std::vector<int> find_all(const std::string & txt ) {
		std::vector<int> occurrs;
		int pos = 0;
		state = 0;
		while (pos < txt.size()) {
			//std::cout << pos << ", " << state << std::endl;
			if ( txt[pos] == pattern[state]) {
				state++;
				pos++;
				if (state == pattern.size()) {
					//std::cout << "matched. " << pos << ", " << state << std::endl;
					occurrs.push_back(pos - pattern.size());
					state = failure[state-1];
				}
			} else {
				if ( state == 0 ) {
					++pos;
				} else {
					state = failure[state-1];
					//std::cout << "failured " << state << std::endl;
				}
			}
		}
		return occurrs;
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

class horspool {
	std::string pattern;
	std::vector<int> skip;
	bool matched;

//	char pattern[], alphabet[];
//	int skip[];

	void initialize() {
		skip.resize( 256 );
		for (int i = 0; i < skip.size(); i++) {
			skip[i] = pattern.size();
		}
		for (int i = 0; i < pattern.size() - 1; i++) {
			skip[pattern[i]] = pattern.size() - i - 1;
		}
	}

public:
	horspool(const char * pat) : pattern(pat), matched(false) {
		initialize();
		return;
	}

	int compare(const std::string txt, const int pos) {
		int patpos = 0, rpos = pos + pattern.size();
		matched = false;
		for (patpos = 0;
				patpos < pattern.size() &&
						(pattern[pattern.size() - 1 - patpos] == txt[rpos - 1 - patpos]);
				++patpos);
		if ( patpos == pattern.size() ) {
			matched = true;
			return 1;
		}
		//std::cout << "pos (pos+size-1) = " << pos << ", state = " << patpos << ", delta = " << skip[txt[rpos - 1 - patpos]] << std::endl;
		return skip[txt[rpos - 1 - patpos]];

	}

	int compare(const std::string::const_reverse_iterator & pos) {
		std::string::const_reverse_iterator patpos = pattern.crbegin();
		std::string::const_reverse_iterator txtpos = pos + (pattern.size() - 1);
		matched = false;
		for ( ; patpos != pattern.crend() && *patpos == *txtpos; --patpos, --txtpos);
		if ( patpos == pattern.crend() ) {
			matched = true;
			return 1;
		}
		return skip[*txtpos];

	}

	// find the 1st occurrence.
	int find(const std::string & txt ) {
		int pos, delta;
		for (pos = 0; pos < txt.size() - pattern.size() + 1; ) {
			delta = compare(txt, pos);
			if ( matched ) {
				return pos;
			}
			pos += delta;
		}
		return pos;
	}

	// find all the occurrences.
	std::vector<int> find_all(const std::string & txt ) {
		std::vector<int> occurrences;
		int pos, delta;
		for (pos = 0; pos < txt.size() - pattern.size() + 1; ) {
			delta = compare(txt, pos);
			if ( matched ) {
				occurrences.push_back(pos);
			}
			pos += delta;
		}
		return occurrences;
	}

	friend std::ostream & operator<<(std::ostream & ost, const horspool & hors) {
		int count = 0;
		ost << "horspool([";
		for (int i = 0; i < hors.pattern.size(); i++) {
			ost << hors.pattern[i] << ", ";
		}
		ost << "], [";
		for (int i = 0; i < hors.skip.size(); i++) {
			if ( hors.skip[i] != hors.pattern.size() ) {
				if ( count != 0 )
					ost << ", ";
				ost << (char) i << ":" << hors.skip[i];
				++count;
			}
		}
		ost << "]) ";
		return ost;
	}

};

int main(const int argc, const char *argv[]) {
	kmp p("abcabc");
	horspool h("abcabc");
	std::string text("abcababcabcabcababacabcabc");

	std::cout << p << std::endl;
	std::cout << text << " (" << text.size() << ")" << std::endl;

	std::cout << "kmp search: " << std::endl;
	std::vector<int> res = p.find_all(text);
	if ( res.size() ) {
		for(std::vector<int>::iterator i = res.begin(); i != res.end(); ++i) {
			std::cout << *i << ", ";
		}
	} else {
		std::cout << "not found.";
	}
	//std::cout << p.find(text);
	std::cout << std::endl << std::endl;

	std::cout << "horspool search: " << std::endl;
	res = h.find_all(text);
	if ( res.size() ) {
		for(std::vector<int>::iterator i = res.begin(); i != res.end(); ++i) {
			std::cout << *i << ", ";
		}
	} else {
		std::cout << "not found.";
	}
	std::cout << std::endl << std::endl;

	return 0;
}
