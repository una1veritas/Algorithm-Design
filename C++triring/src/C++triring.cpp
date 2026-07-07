//============================================================================
// Name        : C++triring.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

template <typename T>
class TriRing {
private:
	static constexpr unsigned int max_count = 3;

private:
		T ring[3];
		unsigned int start, count;
		bool forward;

private:
		inline unsigned int index(int i) const {
			if (i < 0) {
				i += max_count;
			}
			return (start + (forward ? i : max_count-i)) % max_count;
		}

public:
		//default constructor
		TriRing(void) : start(0), count(0), forward(true) { }

		void insert(const T & d) {
			if (count == max_count) {
				cerr << "error: insert TriRing failure." << endl;
				return;
			}
			ring[index(count)] = d; 	// copy data d
			count += 1;
		}

		void insert(unsigned int ix, const T & d) {
			if (count == max_count) {
				cerr << "error: insert TriRing failure." << endl;
				return;
			}
			if ( ix == 0 ) {
				if ( count == 0 ) {
					ring[index(0)] = d;
				} else {
					// count >= 2
					ring[index(-1)] = d;
					start = index(start-1);
				}
			} else if ( ix == 1 ) {
				if (count == 1) {
					ring[index(1)] = d;
				} else {
					// count == 2
					cout << "count = 2 index(-1) = " << index(-1) << endl;
					ring[index(-1)] = d;
					forward = !forward;
				}
			} else if ( ix == 2 ) {
				if (count == 1) {
					ring[index(1)] = d;
				} else {
					// count == 2
					ring[index(2)] = d;
				}
			}
			count += 1;
		}

		void remove_last(void) {
			if (count == 0) {
				cerr << "error: remove TriRing failure." << endl;
				return;
			}
			count -= 1;
		}

		ostream & printOn(ostream & os) const {
			os << "[";
			for(unsigned int i = 0; i < count; ++i) {
				if (i > 0)
					os << ", ";
				//os << i << " -> " << index(i) << ":";
				os << ring[index(i)];
			}
			os << "]";
			os << " start=" << start << ", count=" << count << ", forward=" << forward;
			return os;
		}

		friend ostream & operator<<(ostream & os, const TriRing<T> & tr) {
			return tr.printOn(os);
		}

};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	TriRing<int> tr;
	tr.insert(1);
	tr.insert(2);
	cout << tr << endl;

	tr.insert(1,4);
	cout << tr << endl;
	return 0;
}
