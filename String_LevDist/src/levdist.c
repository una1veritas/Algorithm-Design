/*
 * levdist.c
 *
 *  Created on: 2016/12/12
 *      Author: sin
 */
#include <stdio.h>
#include <stdlib.h>

#include "levdist.h"
#include "debug_table.h"

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

void setframe(long * frame, const long n, const long m) {
	for (long i = 0; i < n + m + 1; i++) {
		frame[i] = ABS(m - i);  // m (pattern, left) frame
	}
}

long dp_edist(long * frame, char t[], long n, char p[], long m) {
	long * dist;
	long col, row;
	long ins, del, repl, result;
	const int lcs_switch = 1;

	//printf("text %s (%d), pattern %s (%d)\n", t, n, p, m);

	dist = (long*) malloc(sizeof(long)*n*m);
	if ( dist == NULL )
		return n+m+1; // error

	// n -- the number of columns (the text length), m -- the number of rows (the pattern length)
	//table calcuration
	// let and top frames of the table corresponds to col = -1, row = -1
	for(col = 0; col < n; col++) { // column, text axis
		for (row = 0; row < m; row++) {  // row, pattern axis
			ins = ( col == 0 ? frame[(m-1)-row] : dist[row + m*(col-1)] ) + 1;
			del = ( row == 0 ? frame[m+1+col] : dist[(row-1) + m*col] ) + 1;
			repl = ( col == 0 || row == 0 ?
					( col == 0 ? frame[m-row] : frame[m+col] ) :
					dist[(row-1) + m*(col-1)] );
			//
			if ( t[col] == p[row] ) {
				if ( ins < del && ins < repl ) {
					repl = ins;
				} else if (del < ins && del < repl ) {
					repl = del;
				}
			} else {
				repl += 1;
				if ( ins <= del && (lcs_switch || ins < repl) ) {
					repl = ins;
				} else if (del < ins && (lcs_switch || del < repl) ) {
					repl = del;
				}
			}
			dist[row + m*col] = repl;
			//printf("[%ld,%ld] %c|%c : %ld/%ld/%ld+%d >%ld,\n", col, row, t[col], p[row], del,ins, repl, (t[col] != p[row]), dist[col*m+row]);
#ifdef DEBUG_TABLE
			debug_table[row+m*col] = dist[row+m*col];
#endif
		}
	}

	result = dist[n*m-1];
	free(dist);
	return result;
}

