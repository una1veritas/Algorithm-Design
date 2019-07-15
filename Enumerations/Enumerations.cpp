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

	int boundary() const {
		int boundary = size() - 1;
		while ( (boundary > 0) && !(elems[boundary - 1] < elems[boundary]) ) {
			--boundary;
		}
		return boundary;
	}

public:
	// initializes the sequence as the first one.
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

	bool hasNextPermutation() const {
		return boundary() > 0;
	}

	bool nextPermutation() {
		int bd = boundary();
		std::cout << "boundary = " << bd << std::endl;
		if (bd == 0) {
			// has no more permutations.
			return false;
		}
		int new_elem = elems[bd - 1];
		int pos;
		for(pos = size() - 1; pos > bd - 1; --pos) {
			if (elems[pos] > new_elem)
				break;
		}
		std::cout << "pos = " << pos << std::endl;
		elems[bd-1] = elems[pos];
		elems[pos] = new_elem;
		// sort [boundary, size() ) in asc. order.
		qsort(elems+bd, size() - bd, sizeof(*elems), int_lessthan);
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

void k_subset(int subset[], int to_go, int from, int n) {
	if (to_go == 0) {
		std::cout << "finished." << std::endl;
		for(int i = 0; i < n; ++i) {
			if ( subset[i] != 0)
				std::cout << i << ", ";
		}
		std::cout << std::endl;
		return;
	}
	if ( to_go > (n - from) ) {
		//std::cout << "exhausted." << std::endl;
		return;
	}
	for(int i = from; i < n; ++i) {
		subset[i] = 1;
		k_subset(subset, to_go - 1, i+1, n);
		subset[i] = 0;
	}
	return;
}

int main(int argc, char **argv) {
	intseq seq(5);

	do {
		std::cout << seq << std::endl;
	} while ( seq.nextPermutation() );

	int set[5];
	k_subset(set, 3, 0, 5);
	printf("Bye.\n");
	return EXIT_SUCCESS;
}
