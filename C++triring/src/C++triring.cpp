//============================================================================
// Name        : C++triring.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdint>

using namespace std;

template <typename T>
class TriRing {
private:
	static constexpr unsigned int max_count = 3;

private:
		T ring[3];
		uint8_t start, count;
		bool forward;

private:
		inline uint8_t index(int i) const {
			if (i < 0) {
				i += max_count;
			}
			return (start + (forward ? uint8_t(i) : uint8_t(max_count - i))) % max_count;
		}

public:
		//default constructor
		TriRing(void) : start(0), count(0), forward(true) { }

		uint8_t size(void) const {
			return count;
		}

		T & operator[](const int & i) {
			if (i < 0 or i >= int(count)) {
				cerr << "error: TriRing index out of range." << endl;
				exit(1);
			}
			return ring[index(i)];
		}

		const T & operator[](const int & i) const {
			if (i < 0 or i >= int(count)) {
				cerr << "error: TriRing index out of range." << endl;
				exit(1);
			}
			return ring[index(i)];
		}

		void insert_back(const T & d) {
			if (count == max_count) {
				cerr << "error: insert into full TriRing." << endl;
				return;
			}
			ring[index(count)] = d; 	// copy data d
			count += 1;
		}

		void insert_front(const T & d) {
			if (count == max_count) {
				cerr << "error: insert into full TriRing." << endl;
				return;
			}
			ring[index(-1)] = d; 	// copy data d
			start = index(start-1);
			count += 1;
		}

		void insert_mid(const T & d) {
			if (count == max_count) {
				cerr << "error: insert into full TriRing." << endl;
				return;
			}
			ring[index(-1)] = d; 	// copy data d
			forward = !forward;
			count += 1;
		}


		void insert(const T & d, const int & ix) {
			if (count == max_count) {
				cerr << "error: insert into full TriRing." << endl;
				return;
			}
			if ( ix == 0 ) {
				insert_front(d);
			} else if ( ix == int(count) ) {
				insert_back(d);
			} else if ( ix > 0 and ix < int(count) ) {
				// if ix == 1
				insert_mid(d);
			} else {
				cerr << "error: insert into TriRing index out of range." << endl;
				return;
			}
		}

		void remove_back(void) {
			if (count == 0) {
				cerr << "error: remove TriRing failure." << endl;
				return;
			}
			count -= 1;
		}

		void remove_front(void) {
			if (count == 0) {
				cerr << "error: remove TriRing failure." << endl;
				return;
			}
			start = index(start+1);
			count -= 1;
		}

		void remove_mid(void) {
			if (count == 0) {
				cerr << "error: remove TriRing failure." << endl;
				return;
			}
			forward = !forward;
			count -= 1;
		}

		void remove( const int & ix) {
			if (count == 0) {
				cerr << "error: remove TriRing failure." << endl;
				return;
			}
			if ( ix == 0 ) {
				remove_front();
			} else if ( ix == int(count) ) {
				remove_back();
			} else if ( ix > 0 and ix < int(count) ) {
				remove_mid();
			} else {
				cerr << "error: insert into TriRing index out of range." << endl;
				return;
			}
		}

		std::ostream & printOn(std::ostream & os) const {
			os << "[";
			for(unsigned int i = 0; i < count; ++i) {
				if (i > 0)
					os << ", ";
				//os << i << " -> " << index(i) << ":";
				os << ring[index(i)];
			}
			os << "]";
			//os << " start=" << int(start) << ", count=" << int(count) << ", forward=" << forward;
			return os;
		}

		friend std::ostream & operator<<(std::ostream & os, const TriRing<T> & tr) {
			return tr.printOn(os);
		}

};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	TriRing<int> tr;
	tr.insert_back(1);
	tr.insert_back(2);
	cout << tr << endl;

	tr.insert(4, 1);
	cout << tr << endl;
	tr[1] = 33;
	cout << tr << endl;

	tr.remove_front();
	tr.insert_back(3);
	cout << tr << ", " << tr[2] << endl;

	tr.remove(1);
	cout << tr << endl;

	tr.remove(0);
	cout << tr << endl;

	return 0;
}
