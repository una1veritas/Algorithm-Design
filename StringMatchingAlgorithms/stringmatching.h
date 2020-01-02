#ifndef _STRINGMATCHING_H_
#define _STRINGMATCHING_H_

#include <iostream>
#include <string>
#include <vector>


class naive {
	std::string pattern;
	int state;

public:
	naive(const char * str) : pattern(str), state(0) { }

	int size() const { return pattern.size(); }

	bool compare(const std::string & txt, const int & pos) {
		for(state = 0; state < pattern.size() && pattern[state] == txt[pos + state]; ++state) {}
		return state == pattern.size();
	}

	int find(const std::string & txt ) {
		int pos; // pos represents the place which will be matched to the last character of the pattern.
		char ch;
		for (pos = 0; pos < txt.size() - pattern.size() + 1; ++pos) {
			if ( compare(txt, pos) ) {
#ifdef FIND_DEBUG
				std::cout << "*" << std::endl;
#endif
				return pos;
			}
#ifdef FIND_DEBUG
			std::cout << "pos = " << pos << ", state = " << state << std::endl;
#endif
			}
		return pos;
	}

	// find all the occurrences.
	std::vector<int> find_all(const std::string & txt ) {
		std::vector<int> occurrences;
		int pos;
		for (pos = 0; pos < txt.size() - pattern.size() + 1; ++pos) {
			if ( compare(txt, pos) ) {
#ifdef FIND_DEBUG
				std::cout << "*";
#endif
				occurrences.push_back(pos);
			}
#ifdef FIND_DEBUG
			std::cout << "pos = " << pos << ", state = " << state << std::endl;
#endif
			}
		return occurrences;
	}

	friend std::ostream & operator<<(std::ostream & ost, const naive & pm) {
		int count = 0;
		ost << "naive('" << pm.pattern << "' ("<< pm.size() << ") )";
		return ost;
	}

};

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
	std::vector<int> delta;
	int state;

//	char pattern[], alphabet[];
//	int skip[];

	void initialize() {
		delta.clear();
		for (int i = 0; i < pattern.size() - 1; i++) {
			for (int j = delta.size(); j <= (int)pattern[i]; ++j)
				delta.push_back(pattern.size());
			delta[pattern[i]] = pattern.size() - i - 1;
		}
	}

public:
	horspool(const char * pat) : pattern(pat), state(0) {
		initialize();
		return;
	}

	int size() const { return pattern.size(); }

	// function for the inner-loop.
	bool compare(const std::string & txt, const int & pos) {
		for (state = 0; state < pattern.size() && (pattern[state] == txt[pos + state]);
				++state);
		return ( state == pattern.size() );
	}

	// find the 1st occurrence.
	// function for the outer-loop.
	int find(const std::string & txt) {
		int pos; // pos represents the place to which the 1st character of the pattern must be matched.
		for (pos = 0; pos < txt.size() - pattern.size() + 1; pos += delta[txt[pos + pattern.size() - 1]]) {
			if ( compare(txt, pos) ) {
#ifdef FIND_DEBUG
				std::cout << "*" << std::endl;
#endif
				return pos;
			}
#ifdef FIND_DEBUG
			std::cout << "pos = " << pos << ", state = " << state << ", delta["<< txt[pos] << "] = " << delta[txt[pos]] << std::endl;
#endif
		}
		return pos;
	}

	// find all the occurrences.
	std::vector<int> find_all(const std::string & txt) {
		std::vector<int> occurrences;
		int pos;
		for (pos = 0; pos < txt.size() - pattern.size() + 1; pos += delta[txt[pos + pattern.size() - 1]]) {
			if ( compare(txt, pos) ) {
#ifdef FIND_DEBUG
				std::cout << "*";
#endif
				occurrences.push_back(pos);
			}
#ifdef FIND_DEBUG
			std::cout << "pos = " << pos << ", state = " << state << ", delta["<< txt[pos] << "] = " << delta[txt[pos]] << std::endl;
#endif
			}
		return occurrences;
	}

	friend std::ostream & operator<<(std::ostream & ost, const horspool & hors) {
		int count = 0;
		ost << "horspool('" << hors.pattern << "' ("<< hors.size() << "), [";
		for (int i = 0; i < hors.delta.size(); i++) {
			if ( hors.delta[i] != hors.pattern.size() ) {
				if ( count != 0 )
					ost << ", ";
				ost << (char) i << ":" << hors.delta[i];
				++count;
			}
		}
		ost << "]) ";
		return ost;
	}

};

#endif /* _STRINGMATCHING_H_ */
