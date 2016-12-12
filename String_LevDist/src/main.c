#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "levdist.h"
#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_B 1048576UL
#define KILO_B 1024UL
#define STR_MAXLENGTH (32 * KILO_B)


int main (int argc, const char * argv[]) {
	char * text, *patt;
	long m, n;
	long d;
	
	stopwatch sw;

	text = malloc(sizeof(char)*STR_MAXLENGTH);
	patt = malloc(sizeof(char)*STR_MAXLENGTH);
	if ( text == NULL || patt == NULL ) {
		fprintf(stderr, "malloc error.\n");
		fflush(stderr);
		goto exit_error;
	}

	if ( argc != 3 )
		return EXIT_FAILURE;

	getcwd(text, STR_MAXLENGTH);
	fprintf(stderr,"Current working directory: \n%s\n", text);
	fflush(stderr);

	if ( textfromfile(argv[1], STR_MAXLENGTH, text) != 0
		|| textfromfile(argv[2], STR_MAXLENGTH, patt) != 0 ) {
		goto exit_error;
	}
	n = (text[STR_MAXLENGTH-1] == 0? strlen(text) : STR_MAXLENGTH);
	m = (patt[STR_MAXLENGTH-1] == 0? strlen(patt) : STR_MAXLENGTH);

	if ( n < 1000 && m < 1000 )
		fprintf(stdout, "Input: %s (%lu), %s (%lu)\n\n", text, n, patt, m);
	else
		fprintf(stdout, "Input: (%lu), (%lu)\n\n", n, m);
	fflush(stdout);
	
	stopwatch_start(&sw);
	if ( n > 5 || m > 5 ) {
		printf("Skip using recursion version.\n");
	} else {
		d = r_edist(text, n, patt, m);
		stopwatch_stop(&sw);
		printf("Edit distance (by recursion): %lu\n", d);
		printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	}
	printf("\n");

	fprintf(stdout, "computing edit distance by DP.\n");
	fflush(stdout);
	stopwatch_start(&sw);
	d = wv_edist(text, n, patt, m);
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %lu\n", d);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	
exit_error:
	free(text);
	free(patt);

    return 0;
}

