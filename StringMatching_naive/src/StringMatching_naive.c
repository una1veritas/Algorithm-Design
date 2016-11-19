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
#include <sys/timeb.h>

#define min(x, y)  (((x) > (y)) ? (y) : (x))

#define STR_MAXLENGTH (2 * 1024 * 1024)

unsigned int findOccurrence(const char *, const unsigned int, const char *, const unsigned int);
int textfromfile(const char * filename, const unsigned int maxsize, char * text);

struct watch {
	struct timeval timevalue;
	struct timeb timebuffer;
	double   elapsed;
	int sec, millisec;
};

typedef struct watch watch;

void watch_start(watch * w) {
	ftime( & w->timebuffer );
	w->sec = w->timebuffer.time;
	w->millisec = w->timebuffer.millitm;
}

void watch_stop(watch * w) {
	ftime( & w->timebuffer );
	w->sec = w->timebuffer.time - w->sec;
	w->millisec = w->timebuffer.millitm - w->millisec;
	w->millisec += w->sec*1000;
	w->elapsed = (double) w->millisec/1000;
}

double watch_millis(watch * w) {
	return w->elapsed;
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

	printf( "Elasped time: %lf\n", watch_millis(&stopwatch) );

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

