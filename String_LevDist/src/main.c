#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "levdist.h"
#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_B 1048576UL
#define KILO_B 1024UL
#define STR_MAXLENGTH (32 * KILO_B)

long * debug_table;
static const char grays[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
static const int grayscale = 62;

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
	if ( n < m ) {
		char * tmp = text;
		text = patt;
		patt = tmp;
		long t = n;
		n = m;
		m = t;
	}

	if ( n < 1000 && m < 1000 )
		fprintf(stdout, "Input: %s \n(%lu), \n%s \n(%lu)\n\n", text, n, patt, m);
	else
		fprintf(stdout, "Input: (%lu), (%lu)\n\n", n, m);
	fflush(stdout);
	
	stopwatch_start(&sw);
	debug_table = (long*) malloc(sizeof(long)*m*n);

	d = dp_edist(debug_table, text, n, patt, m);

	stopwatch_stop(&sw);

	printf("Edit distance (by Pure DP): %lu\n", d);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	printf("\n");

#ifdef DEBUG_TABLE
	// show DP table
	for(long r = 0; r < m; r++) {
		for (long c = 0; c < n; c++) {
			printf("%c", grays[max(0,61 - (int)((debug_table[m*c+r]/(float)(n))*grayscale))] );
			//printf("%3ld ", debug_table[m*c+r]);
		}
		printf("\n");
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
#endif


	fprintf(stdout, "computing edit distance by Waving DP.\n");
	fflush(stdout);
	stopwatch_start(&sw);

	long * lefttopframe = (long*)malloc(sizeof(long)*(m+n+1));
	long * bottomrightframe = (long*)malloc(sizeof(long)*(n-1+m-1+1));
	for(long i = 0; i < m + n + 1; i++) {
		if (i == m)
			lefttopframe[i] = 0;
		else
			lefttopframe[i] = (i - m < 0 ? m - i - 1 : i - m - 1);
		//printf("[%ld] %ld, ", i, lefttopframe[i]);
	}
	//printf("\n");

	d = wv_edist(lefttopframe, bottomrightframe, text, n, patt, m);
	stopwatch_stop(&sw);

	printf("Edit distance (by Weaving DP): %lu\n", d);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));

#ifdef DEBUG_TABLE
	// show DP table
	for(long r = 0; r < m; r++) {
		for (long c = 0; c < n; c++) {
			printf("%c", grays[max(0,61 - (int)((debug_table[m*c+r]/(float)(n))*grayscale))] );
			//printf("%3ld ", debug_table[m*c+r]);
		}
		printf("\n");
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
#endif
	free(debug_table);


exit_error:
	free(text);
	free(patt);

    return 0;
}

