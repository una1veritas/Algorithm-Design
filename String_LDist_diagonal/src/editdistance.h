/*
 * editdistance.h
 *
 *  Created on: 2016/11/26
 *      Author: sin
 */

#ifndef SRC_EDITDISTANCE_H_
#define SRC_EDITDISTANCE_H_

typedef unsigned long ulong;

ulong dptable(ulong * dist, const ulong colsize, const ulong rowsize, const char t[], const ulong tsize, const char p[], const ulong msize);


#endif /* SRC_EDITDISTANCE_H_ */
