/*
 * stopwatch.c
 *
 *  Created on: 2016/11/20
 *      Author: Sin Shimozono
 */

#include "stopwatch.h"

void stopwatch_start(stopwatch * w) {
	w->secs = 0;
	w->millis = 0;
	w->micros = 0;
	gettimeofday(&w->start, NULL);
//	w->cpumicros = clock();
}

void stopwatch_stop(stopwatch * w) {
	gettimeofday(&w->stop, NULL);
	w->secs = w->stop.tv_sec - w->start.tv_sec;
	w->micros = w->stop.tv_usec - w->start.tv_usec;
	w->millis = w->micros / 1000;
	w->micros %= 1000;
	w->millis %= 1000;
}

ulong stopwatch_secs(stopwatch * w) {
	return w->secs;
}

ulong stopwatch_millis(stopwatch * w) {
	return w->millis;
}

ulong stopwatch_micros(stopwatch * w) {
	return w->micros;
}
