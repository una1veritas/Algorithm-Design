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
		std::cout << "boundary = " << boundary << std::endl;
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
		std::cout << "pos = " << pos << std::endl;
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

	std::cout << seq << std::endl;
	seq.nextPermutation();
	std::cout << seq << std::endl;
	seq.nextPermutation();
	std::cout << seq << std::endl;

	printf("Bye.\n");
	return EXIT_SUCCESS;
}
