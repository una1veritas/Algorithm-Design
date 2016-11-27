/*
 * editdistance.c
 *
 *  Created on: 2016/11/26
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>

#include "editdistance.h"

//#define DEBUG_DPTABLE

#define min(x, y)  ((x) <= (y)? (x) : (y))

// assumes the table size (n+1) x (m+1)
ulong dptable(ulong * table, const ulong colsize, const ulong rowsize, const char t[], const ulong n, const char p[], const ulong m) {
	ulong dix, dcol, drow; // diagonal column index, row index
	ulong col, row; // inner diagonal index
	ulong result = n+m+1; // an impossible large value
	ulong ins, del, repl;

#ifdef DEBUG_DPTABLE
	for(int r = 0; r < rowsize; ++r)
		for(int c = 0; c < colsize; ++c)
			table[rowsize*c + r] = 0;
#endif

	// initialize
	for(col = 0; col <= n; ++col) {
		table[col*rowsize] = col;
	}

	for(row = 1; row <= m; ++row) {
		// col == row
		table[row*rowsize+row] = row;
	}

	for(dcol = 0; dcol < n; ++dcol) {
		for(drow = 0; drow < min(dcol+1, m); ++drow) {
			row = drow;
			col = dcol - row;
			//fprintf(stdout, "%3lu:%3lu [%2lu, %2lu] ", dcol+2, (dcol+2)*rowsize+drow+1, col, row);
			ins = table[ ((dcol + 2) - 1)*rowsize + (drow + 1) - 1 ] + 1;
			del = table[ ((dcol + 2) - 1)*rowsize + (drow + 1) ] + 1;
			repl = table[ ((dcol + 2) - 2)*rowsize + (drow + 1) - 1 ]
						  + (t[dcol-row] == p[drow] ? 0 : 1);
			//fprintf(stdout, " %c=%c? ",t[dcol-drow],p[drow] );
			ins = ((ins <= del) ? ins : del);
			table[ (dcol + 2)*rowsize + (drow + 1)]  = (ins < repl ? ins : repl);
		}
	}


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

/*		ins = dist[(row-1) + m*col]+1;
		del = dist[row + m*(col-1)]+1;
		repl = dist[(row-1) + m*(col-1)] + (t[col] == p[row] ? 0 : 1);
		dist[row + m*col] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
	*/

#ifdef DEBUG_DPTABLE
	// show DP table
	for(ulong  r = 0; r < m+1; r++) {
		for(ulong i = 0; i < m+1 - r; ++i)
			fprintf(stdout, "\t");
		for (ulong c = 0; c < colsize; c++) {
			fprintf(stdout, "%3lu\t", table[r + rowsize * c]);
		}
		fprintf(stdout, "\n");
	}

	fprintf(stdout, "[%3lu], ", (m-2)*rowsize + m );
#endif
	result = table[(m-2)*rowsize + m ];
	return result;
}

