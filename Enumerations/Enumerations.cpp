#include <cstdio>
#include <cstdlib>

#include <iostream>

struct intseq {
private:
	int * elems;
	int count;

	static int int_lessthan(const void * a, const void * b) {
		return *(int*)a - *(int*)b;
	}

public:
	intseq(const int & n) {
		elems = new int[n];
		count = n;
		for(int i = 0; i < n; ++i) {
			elems[i] = i + 1;
		}
	}

	const int & size() const { return count; }

	int & operator[](const int & i) {
		return elems[i];
	}

	const int & operator[](const int & i) const {
		return elems[i];
	}

	~intseq() {
		delete [] elems;
	}

	bool nextPermutation() {
		int boundary = size() - 1;
		while ( boundary > 0 ) {
			if ( elems[boundary - 1] < elems[boundary] )
				break;
			--boundary;
		}
		//std::cout << "boundary = " << boundary << std::endl;
		if (boundary == 0) {
			// has no more permutations.
			return false;
		}
		int new_elem = elems[boundary - 1];
		int pos;
		for(pos = size() - 1; pos > boundary - 1; --pos) {
			if (elems[pos] > new_elem)
				break;
		}
		//std::cout << "pos = " << pos << std::endl;
		elems[boundary-1] = elems[pos];
		elems[pos] = new_elem;
		// sort [boundary, size() ) in asc. order.
		qsort(elems+boundary, size() - boundary, sizeof(*elems), int_lessthan);
		return true;
	}

	friend std::ostream & operator<<(std::ostream & st, const intseq & seq) {
		st << "intseq(";
		for(int i = 0; i < seq.size(); ++i) {
			st << seq[i] << ", ";
		}
		st << ") ";
		return st;
	}
};

int main(int argc, char **argv) {
	intseq seq(5);

	do {
	std::cout << seq << std::endl;
	} while( seq.nextPermutation() );

	printf("Bye.\n");
	return EXIT_SUCCESS;
}

/*
intseq(1, 2, 3, 4, 5, )
intseq(1, 2, 3, 5, 4, )
intseq(1, 2, 4, 3, 5, )
intseq(1, 2, 4, 5, 3, )
intseq(1, 2, 5, 3, 4, )
intseq(1, 2, 5, 4, 3, )
intseq(1, 3, 2, 4, 5, )
intseq(1, 3, 2, 5, 4, )
intseq(1, 3, 4, 2, 5, )
intseq(1, 3, 4, 5, 2, )
intseq(1, 3, 5, 2, 4, )
intseq(1, 3, 5, 4, 2, )
intseq(1, 4, 2, 3, 5, )
intseq(1, 4, 2, 5, 3, )
intseq(1, 4, 3, 2, 5, )
intseq(1, 4, 3, 5, 2, )
intseq(1, 4, 5, 2, 3, )
intseq(1, 4, 5, 3, 2, )
intseq(1, 5, 2, 3, 4, )
intseq(1, 5, 2, 4, 3, )
intseq(1, 5, 3, 2, 4, )
intseq(1, 5, 3, 4, 2, )
intseq(1, 5, 4, 2, 3, )
intseq(1, 5, 4, 3, 2, )
intseq(2, 1, 3, 4, 5, )
intseq(2, 1, 3, 5, 4, )
intseq(2, 1, 4, 3, 5, )
intseq(2, 1, 4, 5, 3, )
intseq(2, 1, 5, 3, 4, )
intseq(2, 1, 5, 4, 3, )
intseq(2, 3, 1, 4, 5, )
intseq(2, 3, 1, 5, 4, )
intseq(2, 3, 4, 1, 5, )
intseq(2, 3, 4, 5, 1, )
intseq(2, 3, 5, 1, 4, )
intseq(2, 3, 5, 4, 1, )
intseq(2, 4, 1, 3, 5, )
intseq(2, 4, 1, 5, 3, )
intseq(2, 4, 3, 1, 5, )
intseq(2, 4, 3, 5, 1, )
intseq(2, 4, 5, 1, 3, )
intseq(2, 4, 5, 3, 1, )
intseq(2, 5, 1, 3, 4, )
intseq(2, 5, 1, 4, 3, )
intseq(2, 5, 3, 1, 4, )
intseq(2, 5, 3, 4, 1, )
intseq(2, 5, 4, 1, 3, )
intseq(2, 5, 4, 3, 1, )
intseq(3, 1, 2, 4, 5, )
intseq(3, 1, 2, 5, 4, )
intseq(3, 1, 4, 2, 5, )
intseq(3, 1, 4, 5, 2, )
intseq(3, 1, 5, 2, 4, )
intseq(3, 1, 5, 4, 2, )
intseq(3, 2, 1, 4, 5, )
intseq(3, 2, 1, 5, 4, )
intseq(3, 2, 4, 1, 5, )
intseq(3, 2, 4, 5, 1, )
intseq(3, 2, 5, 1, 4, )
intseq(3, 2, 5, 4, 1, )
intseq(3, 4, 1, 2, 5, )
intseq(3, 4, 1, 5, 2, )
intseq(3, 4, 2, 1, 5, )
intseq(3, 4, 2, 5, 1, )
intseq(3, 4, 5, 1, 2, )
intseq(3, 4, 5, 2, 1, )
intseq(3, 5, 1, 2, 4, )
intseq(3, 5, 1, 4, 2, )
intseq(3, 5, 2, 1, 4, )
intseq(3, 5, 2, 4, 1, )
intseq(3, 5, 4, 1, 2, )
intseq(3, 5, 4, 2, 1, )
intseq(4, 1, 2, 3, 5, )
intseq(4, 1, 2, 5, 3, )
intseq(4, 1, 3, 2, 5, )
intseq(4, 1, 3, 5, 2, )
intseq(4, 1, 5, 2, 3, )
intseq(4, 1, 5, 3, 2, )
intseq(4, 2, 1, 3, 5, )
intseq(4, 2, 1, 5, 3, )
intseq(4, 2, 3, 1, 5, )
intseq(4, 2, 3, 5, 1, )
intseq(4, 2, 5, 1, 3, )
intseq(4, 2, 5, 3, 1, )
intseq(4, 3, 1, 2, 5, )
intseq(4, 3, 1, 5, 2, )
intseq(4, 3, 2, 1, 5, )
intseq(4, 3, 2, 5, 1, )
intseq(4, 3, 5, 1, 2, )
intseq(4, 3, 5, 2, 1, )
intseq(4, 5, 1, 2, 3, )
intseq(4, 5, 1, 3, 2, )
intseq(4, 5, 2, 1, 3, )
intseq(4, 5, 2, 3, 1, )
intseq(4, 5, 3, 1, 2, )
intseq(4, 5, 3, 2, 1, )
intseq(5, 1, 2, 3, 4, )
intseq(5, 1, 2, 4, 3, )
intseq(5, 1, 3, 2, 4, )
intseq(5, 1, 3, 4, 2, )
intseq(5, 1, 4, 2, 3, )
intseq(5, 1, 4, 3, 2, )
intseq(5, 2, 1, 3, 4, )
intseq(5, 2, 1, 4, 3, )
intseq(5, 2, 3, 1, 4, )
intseq(5, 2, 3, 4, 1, )
intseq(5, 2, 4, 1, 3, )
intseq(5, 2, 4, 3, 1, )
intseq(5, 3, 1, 2, 4, )
intseq(5, 3, 1, 4, 2, )
intseq(5, 3, 2, 1, 4, )
intseq(5, 3, 2, 4, 1, )
intseq(5, 3, 4, 1, 2, )
intseq(5, 3, 4, 2, 1, )
intseq(5, 4, 1, 2, 3, )
intseq(5, 4, 1, 3, 2, )
intseq(5, 4, 2, 1, 3, )
intseq(5, 4, 2, 3, 1, )
intseq(5, 4, 3, 1, 2, )
intseq(5, 4, 3, 2, 1, )
Bye.
 */
