/*
 * stopwatch.h
 *
 *  Created on: 2016/11/20
 *      Author: Sin Shimozono
 */

#ifndef SRC_STOPWATCH_H_
#define SRC_STOPWATCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>


typedef unsigned long ulong;

struct stopwatch {
	struct timeval start, stop;
//	clock_t cpumicros;
//	struct tm * tmstart, *tmstop;
	ulong secs, millis, micros;
};

typedef struct stopwatch stopwatch;

void stopwatch_start(stopwatch * w);
void stopwatch_stop(stopwatch * w);
ulong stopwatch_millis(stopwatch * w);
ulong stopwatch_micros(stopwatch * w);
ulong stopwatch_secs(stopwatch * w);

#endif /* SRC_STOPWATCH_H_ */
