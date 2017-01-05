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

	dist = (long*) malloc(sizeof(long)*n*m);
	if ( dist == NULL )
		return n+m+1; // error

	// n -- the number of columns (the text length), m -- the number of rows (the pattern length)
	//table calcuration
	// let and top frames of the table corresponds to col = -1, row = -1
	for(col = 0; col < n; col++) { // column, text axis
		for (row = 0; row < m; row++) {  // row, pattern axis
			if (col == 0)
				ins = frame[(m-1)-row] + 1;
			else
				ins = dist[row + m*(col-1)]+1;
			if ( row == 0 )
				del = frame[m+1+col] + 1;
			else
				del = dist[(row-1) + m*col]+1;
			if ( col == 0 )
				repl = frame[m-row];
			else if ( row == 0 )
				repl = frame[m+col];
			else
				repl = dist[(row-1) + m*(col-1)];
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
			dist[row + m*col] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
			printf("[%ld,%ld] %c|%c : %ld/%ld/%ld+%d >%ld,\n", col, row, t[col], p[row], del,ins, repl, (t[col] != p[row]), dist[col*m+row]);
#ifdef DEBUG_TABLE
			debug_table[row+m*col] = dist[row+m*col];
#endif
		}
	}

	result = dist[n*m-1];
	free(dist);
	return result;
}

#define SNAKE_HEADS
long weaving_edist(long * frame, const char t[], const long n, const char p[], const long m)
{
	long col, row;
	long del, ins, repl; // del = delete from pattern, downward; ins = insert to pattern, rightward
	long warp_start, warp_last;

	const int lcs_switch = 1;

#ifdef SNAKE_HEADS
	long snake[n+m+1];
	struct {
		long warp, tail, head;
	} heads[n*m];
	long numheads = 0;
#endif // SNAKE_HEADS

	if (frame == NULL)
		return n+m+1;

#ifdef SNAKE_HEADS
	for(long i = 0; i < n+m; i++) {
		snake[i] = frame[i];
	}
#endif
	for (long depth = 0; depth <= (n - 1) + (m - 1); depth++) {
		warp_start = ABS((m - 1) - depth);
		if (depth < n) {
			warp_last = depth + (m - 1);
		}
		else {
			warp_last = ((n - 1) << 1) + (m - 1) - depth;
		}
		// mywarpix = (thix<<1) + (depth & 1);
		//printf("depth %ld [%ld, %ld]: warpix ", depth, warp_start, warp_last);
		for (long warpix = warp_start; warpix <= warp_last; warpix += 2) {
			if (warpix < 0 || warpix > n + m + 1) {
				printf("warp value error: %ld\n", warpix);
				//fflush(stdout);
			}
			col = (depth + warpix - (m - 1))>>1;
			row = (depth - warpix + (m - 1))>>1;

			//printf("%ld = (%ld, %ld), ", warpix, col, row);
			//
			del = frame[warpix+1+1] + 1;
			ins = frame[warpix-1+1] + 1;
			repl = frame[warpix+1];

			//repl = frame[warpix+1] + (t[col] != p[row]);
			//printf("%ld: %ld [%ld,%ld] %c|%c : %ld/%ld/%ld+%ld,\n",depth, warpix, col,row,t[col],p[row], del,ins, frame[warpix], (t[col] != p[row]));
			//
			if ( t[col] == p[row] ) {
				if (del < ins && del < repl) {
					repl = del;
				} else if ( ins < del && ins < repl ) {
					repl = ins;
				}
			} else /* ( t[col] != p[row] ) */ {
				repl += 1;
				if (del <= ins && (lcs_switch || del < repl) ) {
					repl = del;
				} else if ( ins < del && (lcs_switch || ins < repl) ) {
					repl = ins;
				}
			}
			//
#ifdef SNAKE_HEADS
			if ( t[col] != p[row] ) {
				if ( (snake[warpix+1] < depth - 2) ) {
					heads[numheads].warp = warpix+1;
					heads[numheads].tail = snake[warpix+1];
					heads[numheads].head = depth - 2;
					numheads++;
				}
				snake[warpix+1] = depth;
			} else if ( col == n-1 || row == m-1 ) {
				if ( (snake[warpix+1] < depth - 2) ) {
					heads[numheads].warp = warpix+1;
					heads[numheads].tail = snake[warpix+1];
					heads[numheads].head = depth;
					numheads++;
				}
			}
#endif
			//
			frame[warpix+1] = repl;
#ifdef DEBUG_TABLE
			debug_table[m*col + row] = repl;
#endif
		}
#ifdef SNAKE_HEADS
		for(long i = 0; i < n+m+1; i ++) {
			if ( i < warp_start || i > warp_last || (((i - warp_start) & 1) == 1) ) {
				printf("   ");
			} else {
				printf("%2ld ", snake[i+1]);
			}
		}
		printf("\n");
#endif
	}

#ifdef SNAKE_HEADS
		for(long i = 0; i < numheads; i ++) {
			printf("snake head: %ld: %ld -- %ld\n", heads[i].warp - m, heads[i].tail, heads[i].head);
		}
		printf("\n");
#endif


	return frame[n];
}
