/*
 ============================================================================
 Name        : StringMatching_Naive.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#define min(x, y)  (((x) > (y)) ? (y) : (x))

#define MEGA_BIN 1048576UL
#define KILO_BIN 1024UL
#define STR_MAXLENGTH (4 * MEGA_BIN)

unsigned int findOccurrence(const char *, const unsigned int, const char *, const unsigned int);
int textfromfile(const char * filename, const unsigned int maxsize, char * text);

typedef unsigned long ulong;

struct watch {
	struct timeval start, stop;
//	clock_t cpumicros;
//	struct tm * tmstart, *tmstop;
	ulong sec, millis, micros;
};

typedef struct watch watch;

void watch_start(watch * w) {
	w->sec = 0;
	w->millis = 0;
	w->micros = 0;
	gettimeofday(&w->start, NULL);
//	w->cpumicros = clock();
}

void watch_stop(watch * w) {
	gettimeofday(&w->stop, NULL);
	w->sec = w->stop.tv_sec - w->start.tv_sec;
	w->micros = w->stop.tv_usec - w->start.tv_usec;
	w->millis = w->micros / 1000;

}

ulong watch_millis(watch * w) {
	return w->millis;
}

ulong watch_micros(watch * w) {
	return w->micros;
}

int main(int argc, char * argv[]) {
	char * text, *patt;
	unsigned int n, m;
	int i;

	struct watch stopwatch;

	if ( argc != 3 )
		return EXIT_FAILURE;

	text = malloc(sizeof(char)*STR_MAXLENGTH);
	patt = malloc(sizeof(char)*STR_MAXLENGTH);

	if ( textfromfile(argv[1], STR_MAXLENGTH, text) != 0
		|| textfromfile(argv[2], STR_MAXLENGTH, patt) != 0 ) {
		goto exit_error;
	}

	n = strlen(text);
	m = strlen(patt);

	printf("Text (%d): \n", n);
	for(i = 0; i < min(n, 256); ++i )
		printf("%c",text[i]);
	if ( !(i < 256) )
		printf("\n...");
	printf("\nPattern (%d): \n", m);
	for(i = 0; i < min(m, 256); ++i )
		printf("%c",patt[i]);
	if ( !(i < 256) )
		printf("\n...");
	printf("\n\n");

	watch_start(&stopwatch);

	printf("Search start.\n");
	unsigned int pos = findOccurrence(text, n, patt, m);

	watch_stop(&stopwatch);

	printf( "Elasped time: %lu milli %lu micro secs.\n",
			watch_millis(&stopwatch), watch_micros(&stopwatch) % 1000);

	printf("Found at %u\n", pos);

	free(text);
	free(patt);

	return EXIT_SUCCESS;

exit_error:
	free(text);
	free(patt);

	return EXIT_FAILURE;
}

unsigned int findOccurrence(const char* t, const unsigned int n, const char * p, const unsigned int m) {
	unsigned int pos, l;

	for(pos = 0; pos < n - m + 1; ++pos) {
		//printf("@%u, %u\n",pos, n-m+1);
		for(l = 0; l < m; ++l) {
			if ( t[pos+l] != p[l] ) break;
		}
		if ( l == m )
			return pos;
	}
	return n;
}

int textfromfile(const char * filename, const unsigned int maxsize, char * text) {
	FILE * fp;
	int pos;
	char * ptr;

	fp = fopen(filename, "r");
	if ( fp == NULL ) {
		fprintf(stderr, "error: open file %s failed.\n", filename);
		return -1;
	}
	for(ptr = text, pos = 0; pos < maxsize; ++ptr, ++pos) {
		int c = fgetc(fp);
		if ( c == EOF )
			break;
		*ptr = (char) c;
	}
	return EXIT_SUCCESS;
}

