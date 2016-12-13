/*
 * levdist.c
 *
 *  Created on: 2016/12/12
 *      Author: sin
 */
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_TABLE

#define min(x, y)   ((x) > (y)? (y) : (x))
#define max(x, y)   ((x) < (y)? (y) : (x))

static const char grays[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
static const int grayscale = 62;

long r_edist(char s[], int m, char t[], int n) {
	long a, b, c;
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

long dp_edist(char t[], long n, char p[], long m) {
	long * dist;
	long result = 0;
	long ins, del, repl;

	dist = (long *) malloc(sizeof(long)*m*n);
	if ( dist == NULL )
		return 0;

	// initialize cells in the top row or in the left-most column
	// n -- the number of columns, m -- the number of rows
	long col = 0;
	long row = 0;
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
	for(long c = 1; c < n; c++) { // column, text axis
		for (long r = 1; r < m; r++) {  // row, pattern axis
			ins = dist[(r-1) + m*c]+1;
			del = dist[r + m*(c-1)]+1;
			repl = dist[(r-1) + m*(c-1)] + (t[c] == p[r] ? 0 : 1);
			dist[r + m*c] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
	}

#ifdef DEBUG_TABLE
	// show DP table
	for(long r = 0; r < m; r++) {
		for (long c = 0; c < n; c++) {
			printf("%3ld ", dist[m*c+r]);
		}
		printf("\n");
	}
#endif

	result = dist[n * m - 1];
	free(dist);
	return result;
}

long wv_edist(long * inframe, long * outframe, char t[], long n, char p[], long m) {
	long * dist;
	long result = n+m+1;
	long col, row;
	long del, ins, repl; // del = delete from pattern, downward; ins = insert to pattern, rightward
	long thix;
	long thread_min, thread_max;

	dist = (long *) malloc(sizeof(long)*m*n);
	if ( dist == NULL )
		return -1;

	for(long depth = 0; depth < n+m; depth++) {
		thread_min = -depth;
		if ( !(depth < m) ) {
			thread_min += (depth + 1 - m)<<1;
		}
		thread_max = depth;
		if ( !(depth < n) )
			thread_max -= (depth + 1 - n)<<1;
		//printf("thread_max = %ld\n", thread_max);
		fflush(stdout);
		for(long thread = thread_min; thread <= thread_max; thread += 2) {
			col = (depth + thread)>>1;
			row = (depth - thread)>>1;
			thix = (thread + 2*m) % (2*m);
			//
			if ( row == 0 ) {
				del = inframe[m+1+col] + 1;
			} else {
				del = dist[m*col + (row -1)] + 1;
			}
			if ( col == 0 ) {
				ins = inframe[m-1-row] + 1;
			} else {
				ins = dist[m*(col-1) + row] + 1;
			}
			if ( row == 0 ) {
				repl = inframe[m+1+col-1];
			} else if (col == 0) {
				repl = inframe[m-1-(row-1)];
			} else {
				repl = dist[m*(col-1)+(row-1)];
			}
			repl += (t[col] != p[row]);
			//
			if ( del < ins )
				ins = del;
			if ( ins < repl )
				repl = ins;
			//
			dist[m*col + row] = repl;

			//printf("%ld: %ld, %ld; ", depth, col, row);
			//printf("\n");
		}
		//printf("\n");
		//fflush(stdout);
	}
	printf("table computation finished.\n");
	fflush(stdout);

#ifdef DEBUG_TABLE
	// show DP table
	for(long r = 0; r < m; r++) {
		for (long c = 0; c < n; c++) {
			printf("%c", grays[max(0,61 - (int)((dist[m*c+r]/(float)(n))*grayscale))] );
			//printf("%3ld ", dist[m*c+r]);
		}
		printf("\n");
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
#endif

	result = dist[n * m - 1];

	free(dist);
	return result;
}
