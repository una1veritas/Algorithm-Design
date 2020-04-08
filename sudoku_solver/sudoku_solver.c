#include <stdio.h>
#include <stdlib.h>

const static int rows = 9;

void show_cells(const int rows, const int * cells);
int read_input(const int argc, const char * argv[], int * cells);
void init_ans(int * ans, const int * cells);
void sort_row(int * begin, int * end);
int next_row(int * begin, int * end);

int main(const int argc, const char * argv[]) {
	int cells[rows*rows];

	if ( read_input(argc, argv, cells) )
		return EXIT_FAILURE;
	show_cells(rows, cells);
	printf("\n");

	int ans[rows*rows];
	init_ans(ans, cells);

	show_cells(rows, (const int *) ans);
	printf("\n");
	while ( next_row(ans, ans+rows) );

	show_cells(rows, (const int *) ans);
	printf("\n");

	return 0;
}

int next_row(int * begin, int * end) {
	int cnt;
	int t;
	int * ptr, * prev;

	for(ptr = end - 1; *ptr == 0; --ptr) {
		if ( ptr == begin )
			return 0;
	}
	do {
		prev = ptr;
		for( ptr -= 1; *ptr == 0; --ptr) {
			if ( ptr == begin )
				return 0;
		}
		//printf("%d > %d?\n", *ptr, *prev);
	} while ( *ptr > *prev && ptr != begin);
	if ( ptr == begin && *ptr > *prev )
		return 0;
	sort_row(prev, end);
	for( ; *ptr > *prev || *prev == 0 ; ++prev);
	t = *ptr;
	*ptr = *prev;
	*prev = t;

	return 1;
}


void init_ans(int * ans, const int * cells) {
	int nums[rows];
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < rows; ++c) {
			ans[r*rows + c] = 0;
			nums[c] = c+1;
		}
		for(int c = 0; c < rows; ++c) {
			if ( cells[r*rows+c] != 0 ) {
				nums[cells[r*rows+c]-1] = 0;
			}
		}
		for(int c = 0, nc = 0; c < rows && nc < rows; ) {
			if ( cells[r*rows+c] != 0 ) {
				ans[r*rows+c] = 0;
				++c;
				continue;
			} else {
				if ( nums[nc] == 0 ) {
					++nc;
					continue;
				}
				ans[r*rows+c] = nums[nc];
				++c;
				++nc;
			}
		}
	}
}

void sort_row(int * begin, int * end) {
	int cnt;
	int t;
	int * ptr, * next;
	do {
		cnt = 0;
		for(ptr = begin; ptr+1 != end; ++ptr) {
			if ( *ptr == 0 )
				continue;
			for(next = ptr + 1; *next == 0; ++next) {
				if ( next == end)
					break;
			}
			if ( next == end )
				continue;
			if ( *ptr > *next ) {
				t = *ptr;
				*ptr = *next;
				*next = t;
				++cnt;
			}
		}
	} while ( cnt > 0 );
}

int read_input(const int argc, const char * argv[], int * cells) {
	if ( argc <= rows*rows ) {
		fprintf(stderr, "give me an input in '0 0 3 0 5 0 0 9 ... 0 9 0' format.\n");
		return EXIT_FAILURE;
	}
	int cellnum = 0;
	for(int i = 1; i < argc && cellnum <= 81; ++i) {
		cells[cellnum] = atoi(argv[i]);
		cellnum += 1;
	}
	if ( cellnum != rows*rows ) {
		fprintf(stderr,"there are %d digits!! give a sequence of exact rows x rows numbers!!", cellnum);
		return EXIT_FAILURE;
	}
	return 0;
}

void show_cells(const int rows, const int * cells) {
	for(int r = 0; r < rows; ++r) {
		printf("+");
		for(int c = 0; c < rows; ++c) {
			printf("---+");
		}
		printf("\n");
		printf("|");
		for(int c = 0; c < rows; ++c) {
			if ( cells[r*rows + c] == 0 )
				printf("   |");
			else
				printf(" %d |", cells[r*rows + c]);
		}
		printf("\n");
		if (r+1 == rows) {
			printf("+");
			for(int c = 0; c < rows; ++c) {
				printf("---+");
			}
			printf("\n");
		}
	}
}

