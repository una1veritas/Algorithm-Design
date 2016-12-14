/*
 * levdist.c
 *
 *  Created on: 2016/12/12
 *      Author: sin
 */
#include <stdio.h>
#include <stdlib.h>

#include "levdist.h"

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

long dp_edist(long * dist, char t[], long n, char p[], long m) {
	long ins, del, repl;

	if ( dist == NULL )
		return n+m+1;

	// initialize cells in the top row or in the left-most column
	// n -- the number of columns, m -- the number of rows
	long col = 0;
	long row = 0;

	//[0, 0]
	ins = col + 1; // always == del
	repl = (p[0] == t[col] ? 0 : 1);
	dist[0] = (ins < repl ? ins : repl);

	//[col, 0]
	for(col = 1; col < n; ++col) {
		// row == 0
		del = (col + 1) + 1;
		ins = dist[m*(col-1)] + 1;
		repl = col + (p[0] == t[col] ? 0 : 1);
		ins = (ins < del ? ins : del);
		dist[m * col + 0] = (ins < repl ? ins : repl);
	}
	//[0, row]
	for(row = 1; row < m; ++row) {
		// col == 0
		del = dist[row - 1] + 1;
		ins = row + 1 + 1;
		repl = row + (p[row] == t[0] ? 0 : 1);
		ins = (ins < del ? ins : del);
		dist[m*0 + row]  = (ins < repl ? ins : repl);
	}

	//table calcuration
	for(long c = 1; c < n; c++) { // column, text axis
		for (long r = 1; r < m; r++) {  // row, pattern axis
			del = dist[(r-1) + m*c]+1;
			ins = dist[r + m*(c-1)]+1;
			repl = dist[(r-1) + m*(c-1)] + (t[c] == p[r] ? 0 : 1);
			dist[r + m*c] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
	}

	return dist[n * m - 1];
}

void wv_setframe(long * frame,  const char t[], const long n, const char p[], const long m) {
	for(long i = 0; i < m + n + 1; i++) {
		frame[i] = (i - m < 0 ? m - i : i - m );
	}
}

long wv_edist(long * frame, const char t[], const long n, const char p[], const long m) {
	long * threads;
	long result = n+m+1;
	long col, row;
	long del, ins, repl; // del = delete from pattern, downward; ins = insert to pattern, rightward
	long thix, lthix, rthix;
	long thread_min, thread_max;

	threads = (long *) malloc(sizeof(long)*m*2);
	if ( threads == NULL )
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
		//fflush(stdout);
		for(long thread = thread_min; thread <= thread_max; thread += 2) {
			col = (depth + thread)>>1;
			row = (depth - thread)>>1;
			lthix = (thread + 2*m - 1) % (2*m);
			thix = (lthix + 1)%(2*m);//(thread + 2*m) % (2*m);
			rthix = (thix+1)%(2*m);
			//
			if ( row == 0 ) {
				del = frame[m+1+col] + 1;
				printf("del: %ld, %ld\n", ((m+1+col) -m+2*m)%(2*m), rthix);
			} else {
				//del = debug_table[m*col + (row - 1)] + 1;
				del = threads[rthix]+1;
			}
			if ( col == 0 ) {
				ins = frame[m-1-row] + 1;
				printf("ins: %ld, %ld\n", ((m-1-row)-m+2*m)%(2*m), lthix);
			} else {
				//ins = debug_table[m*(col-1) + row] + 1;
				ins = threads[lthix]+1;
				//printf("thr[%d]\n",(thix+2*m-1)%(2*m));
			}
			if ( row == 0 ) {
				repl = frame[m+1+col-1];
			} else if (col == 0) {
				repl = frame[m-1-(row-1)];
			} else {
				//repl = debug_table[m*(col-1) + (row-1)];
				repl = threads[thix];
			}
			repl += (t[col] != p[row]);

			//printf("%ld: (%ld, %ld) ", depth, col, row);
			//printf("%ld/%ld/%ld, ", del, ins, repl);
			//printf("\n");

			//
			if ( del < ins )
				ins = del;
			if ( ins < repl )
				repl = ins;
			//
			threads[thix] = repl;
			//printf("threads[%d] %d, \n", thix, repl);
			debug_table[m*col + row] = repl;

		}
		//printf("\n");
		//fflush(stdout);
	}
	//printf("table computation finished.\n");
	//fflush(stdout);

	result = threads[(n+m)%(2*m)];

	free(threads);
	return result;
}
