/*
 * editdistance.c
 *
 *  Created on: 2016/11/26
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>

#include "editdistance.h"

#define DEBUG_DPTABLE

#define min(x, y)  ((x) <= (y)? (x) : (y))

// assumes the table size (n+1) x (m+1)
long dptable(long * table, const long colsize, const long rowsize, const char t[], const long n, const char p[], const long m) {
	long dix, dcol, drow; // diagonal column index, row index
	long col, row; // inner diagonal index
	long result = n+m+1; // an impossible large value
	long ins, del, repl;

#ifdef DEBUG_DPTABLE
	// clear table elements
	for(long r = 0; r < rowsize; ++r)
		for(long c = 0; c < colsize; ++c)
			table[rowsize*c + r] = 0;
#endif

	// initialize
	for(col = 0; col <= n; ++col) {
		if ( col <= m ) {
			dix = col*(col+1)/2;
		} else {
			dix = m*(m+1)/2+(m+1)*(col-m);
		}
		table[dix] = col;
	}
	fprintf(stdout, "\n");

	for(row = 1; row <= m; ++row) {
		// m <= n
		dix = (row+1)*(row+2)/2 - 1;
		table[dix] = row;
	}

	for(dcol = 1; dcol <= m; ++dcol) {
		for(drow = 1; drow <= dcol; ++drow) {
			dix = dcol*(dcol+1)/2 + drow;
			row = drow;
			col = dcol - row;
			//fprintf(stdout, "%3lu:%3lu [%2lu, %2lu] ", dcol+2, (dcol+2)*rowsize+drow+1, col, row);
			ins = table[ dix - dcol - 1 ] + 1;
			del = table[ dix - dcol ] + 1;
			repl = table[ dix - dcol - (dcol - 1) - 1]
						  + (t[dcol-row] == p[drow] ? 0 : 1);
			//fprintf(stdout, " %c=%c? ",t[dcol-drow],p[drow] );
			ins = ((ins <= del) ? ins : del);
			table[ dix]  = (ins < repl ? ins : repl);
		}
	}

/*
	for(dcol = n; dcol < n+m; ++dcol) {
		for(drow = dcol + 1 - n; drow < m; ++drow) {
			row = drow;
			col = dcol - row;
			//DEBUGOUT fprintf(stdout, "%3lu:%3lu [%2lu, %2lu] ", (dcol+2) %(n+2), ((dcol+2)%(n+2))*rowsize+drow+1, col, row);
			ins = table[ (((dcol + 2) - 1) % (n+2)) *rowsize + (drow + 1) - 1 ] + 1;
			del = table[ (((dcol + 2) - 1)% (n+2))*rowsize + (drow + 1) ] + 1;
			repl = table[ (((dcol + 2) - 2)% (n+2))*rowsize + (drow + 1) - 1 ]
						  + (t[dcol-row] == p[drow] ? 0 : 1);
			//fprintf(stdout, " %c=%c? ",t[dcol-drow],p[drow] );
			ins = ((ins <= del) ? ins : del);
			table[ ((dcol + 2)% (n+2))*rowsize + (drow + 1)]  = (ins < repl ? ins : repl);
#ifdef DEBUG_DPTABLE
			//table[(dcol + 2)*rowsize + (drow + 1)] = table[ ((dcol + 2)% (n+2))*rowsize + (drow + 1)];
#endif
			}
	}
*/

#ifdef DEBUG_DPTABLE
	// show DP table
	for(row = 0; row <= m; row++) {
		for (col = 0; col <= n; col++) {
			if ( col + row <= m ) {
				dix = (col + row)*(col + row + 1)/2 + row;
			} else if (col+row<=n) {
				dix = (m+1)*(m+2)/2 + (m+1)*(col - m - 1 + row) + row;
			} else {
				dix = (m+1)*(m+2)/2 + (m+1)*(col - m - 1 + row) + row - (col+row-n)*(col+row-n+1)/2;
			}
			fprintf(stdout, "%2lu\t", table[dix]);
		}
		fprintf(stdout, "\n");
	}

	fprintf(stdout, "[%3lu], ", (m-2)*rowsize + m );
#endif
	result = table[(m-2)*rowsize + m ];
	return result;
}

