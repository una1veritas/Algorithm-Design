#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_B 1048576UL
#define KILO_B 1024UL
#define STR_MAXLENGTH (32 * KILO_B)

typedef unsigned long ulong;


int r_edist(char s[], int m, char t[], int n) {
	int a, b, c;
	if (m == 0 && n == 0)
		return 0;
	if (m == 0)
		return n;
	if (n == 0)
		return m;
	a = r_edist(s, m, t, n-1) + 1;
	b = r_edist(s, m-1, t, n) + 1;
	c = r_edist(s, m-1, t, n-1) + ((s[m-1] == t[n-1])? 0 : 1);
	return (a < b ? (a < c ? a: c): (b < c ? b : c));
}

unsigned long dp_edist(char t[], unsigned long n, char p[], unsigned long m) {
	unsigned long * dist;
	unsigned long result = 0;
	unsigned long ins, del, repl;
	
	dist = (unsigned long *) malloc(sizeof(unsigned long)*m*n);
	if ( dist == NULL )
		return 0;
	
	// initialize cells in the top row or in the left-most column
	// n -- the number of columns, m -- the number of rows
	ulong col = 0;
	ulong row = 0;
	ins = col + 1;
	repl = (p[0] == t[col] ? 0 : 1);
	dist[0] = (ins < repl ? ins : repl);

	for(col = 1; col < n; ++col) {
		// row == 0
		ins = col + 1;
		repl = col - 1 + (p[0] == t[col] ? 0 : 1);
		dist[0 + m * col] = (ins < repl ? ins : repl);
	}
	for(row = 1; row < m; ++row) {
		// col == 0
		del = row + 1;
		repl = row - 1 + (p[row] == t[0] ? 0 : 1);
		dist[row + 0]  = (del < repl ? del : repl);
	}

	//table calcuration
	for(ulong c = 1; c < n; c++) { // column, text axis
		for (ulong r = 1; r < m; r++) {  // row, pattern axis
			ins = dist[(r-1) + m*c]+1;
			del = dist[r + m*(c-1)]+1;
			repl = dist[(r-1) + m*(c-1)] + (t[c] == p[r] ? 0 : 1);
			dist[r + m*c] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
	}

#ifdef DEBUG_TABLE
	// show DP table
	for(ulong r = 0; r < m; r++) {
		for (ulong c = 0; c < n; c++) {
			printf("%d\t", dist[m*c+r]);
		}
		printf("\n");
	}
#endif

	result = dist[n * m - 1];
	free(dist);
	return result;
}

int main (int argc, const char * argv[]) {
	char * text, *patt;
	unsigned long m, n;
	unsigned long d;
	
	stopwatch sw;

	text = malloc(sizeof(char)*STR_MAXLENGTH);
	patt = malloc(sizeof(char)*STR_MAXLENGTH);
	if ( text == NULL || patt == NULL ) {
		fprintf(stderr, "malloc error.\n");
		fflush(stderr);
		goto exit_error;
	}

	if ( argc != 3 )
		return EXIT_FAILURE;

	getcwd(text, STR_MAXLENGTH);
	fprintf(stderr,"Current working directory: \n%s\n", text);
	fflush(stderr);

	if ( textfromfile(argv[1], STR_MAXLENGTH, text) != 0
		|| textfromfile(argv[2], STR_MAXLENGTH, patt) != 0 ) {
		goto exit_error;
	}
	n = (text[STR_MAXLENGTH-1] == 0? strlen(text) : STR_MAXLENGTH);
	m = (patt[STR_MAXLENGTH-1] == 0? strlen(patt) : STR_MAXLENGTH);

	if ( n < 1000 && m < 1000 )
		fprintf(stdout, "Input: %s (%lu), %s (%lu)\n\n", text, n, patt, m);
	else
		fprintf(stdout, "Input: (%lu), (%lu)\n\n", n, m);
	fflush(stdout);
	
	stopwatch_start(&sw);
	if ( n > 5 || m > 5 ) {
		printf("Skip using recursion version.\n");
	} else {
		d = r_edist(text, n, patt, m);
		stopwatch_stop(&sw);
		printf("Edit distance (by recursion): %lu\n", d);
		printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	}
	printf("\n");

	fprintf(stdout, "computing edit distance by DP.\n");
	fflush(stdout);
	stopwatch_start(&sw);
	d = dp_edist(text, n, patt, m);
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %lu\n", d);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	
exit_error:
	free(text);
	free(patt);

    return 0;
}

