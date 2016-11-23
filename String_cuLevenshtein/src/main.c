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

ulong dp_edist(ulong * dist, const char t[], const ulong n, const char p[], const ulong m) {
	ulong result = n+m+1;
	ulong ins, del, repl;
	
	// initialize cells in the top row or in the left-most column
	// n -- the number of columns, m -- the number of rows
	for(ulong col = 0; col < n; ++col) {
		// row == 0
		dist[0 + m * col] = (p[0] == t[col] ? col : col+1);
	}
	for(ulong row = 0; row < m; ++row) {
		// col == 0
		dist[row + 0] = (p[row] == t[0] ? row : row+1);
	}

	// table calcuration, assuming m <= n
	// in left top triangle
	// dix is the diagonal depth from the left top of the `inner' table from (1,1)
	ulong dix, innx;
	ulong col, row;
	for(dix = 0; dix < m - 2; ++dix) {
		for(innx = dix * (dix+1) / 2; innx < (dix+1) * (dix+2) / 2 ; ++innx) {
			row = innx + 1 - dix * (dix+1) / 2;
			col = dix - (row - 1) + 1;
			fprintf(stdout, "%lu (%lu, %lu), ", innx, row, col);
			//
			ins = dist[(row-1) + m*col]+1;
			del = dist[row + m*(col-1)]+1;
			repl = dist[(row-1) + m*(col-1)] + (t[col] == p[row] ? 0 : 1);
			dist[row + m*col] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
		fprintf(stdout, "\n");
		fflush(stdout);
	}

	// helical rectangles
	//innx = dix*(dix+1)/2; // this value already has been set
	ulong offset = dix*(dix+1)/2;
	fprintf(stdout, "inner array (thread) index %lu\n", innx);
	for(ulong hix = 0, dix = m-1 ; dix < n - 1 /* hix < n - m - 1 */; ++dix, ++hix ) {
		// hix is the column id in helical rectangles of the inner rectangle
		for( innx = offset + hix*(m-1); innx < offset + (hix+1)*(m-1); ++innx ) {
			fprintf(stdout, "%lu (%lu, %lu), ", innx, row, col);
			//
			ins = dist[(row-1) + m*col]+1;
			del = dist[row + m*(col-1)]+1;
			repl = dist[(row-1) + m*(col-1)] + (t[col] == p[row] ? 0 : 1);
			dist[row + m*col] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
		fprintf(stdout, "\n");
		fflush(stdout);
	}

	// bottom right triangles
	fprintf(stdout, "inner array (thread) index %lu\n", innx);
	fprintf(stdout, "the bottom right triangle.\n");

/*		ins = dist[(row-1) + m*col]+1;
		del = dist[row + m*(col-1)]+1;
		repl = dist[(row-1) + m*(col-1)] + (t[col] == p[row] ? 0 : 1);
		dist[row + m*col] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
	*/

	// show DP table 
	/*
	for(i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) { 
			printf("%d\t", d[i][j]);
		}
		printf("\n");
	}
	 */
	result = dist[n * m - 1];

	return result;
}

int main (int argc, const char * argv[]) {
	char * text, *patt;
	ulong m, n, dist;
	ulong * dptable;
	
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

	n = textfromfile(argv[1], STR_MAXLENGTH, text);
	m = textfromfile(argv[2], STR_MAXLENGTH, patt);
	if ( n == 0 || m == 0 ) {
		goto exit_error;
	}
	if ( n < m ) {
		ulong t = n;
		n = m;
		m = t;
		char * ptr = text;
		text = patt;
		patt = ptr;
	}

	if ( n < 1000 && m < 1000 )
		fprintf(stdout, "Input: %s (text %lu),\n %s (pattern %lu)\n\n", text, n, patt, m);
	else
		fprintf(stdout, "Input: (text %lu), (pattern %lu)\n\n", n, m);
	fflush(stdout);
	
	stopwatch_start(&sw);
	if ( n > 16 || m > 16 ) {
		printf("Skip using recursion version.\n");
	} else {
		dist = r_edist(text, n, patt, m);
		stopwatch_stop(&sw);
		printf("Edit distance (by recursion): %lu\n", dist);
		printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	}
	printf("\n");

	fprintf(stdout, "computing edit distance by DP.\n");
	fflush(stdout);
	stopwatch_start(&sw);

	dptable = (ulong *) malloc(sizeof(ulong)*m*n);
	if ( dptable != NULL) {
		dist = dp_edist(dptable, text, n, patt, m);
		free(dptable);
	} else {
		fprintf(stderr, "DP table malloc has failed.\n");
		fflush(stderr);
	}
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %lu\n", dist);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	
exit_error:
	free(text);
	free(patt);

    return 0;
}

