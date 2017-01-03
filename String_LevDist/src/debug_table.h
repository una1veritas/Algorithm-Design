/*
 * debug_table.h
 *
 *  Created on: 2017/01/03
 *      Author: sin
 */

#ifndef SRC_DEBUG_TABLE_H_
#define SRC_DEBUG_TABLE_H_

#define DEBUG_TABLE

#ifdef DEBUG_TABLE
extern long * debug_table;

void show_table(long * table, long n, long m);
long compare_table(long * t0, long * t1, long n, long m);
#endif


#endif /* SRC_DEBUG_TABLE_H_ */
