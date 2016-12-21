#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "levdist.h"
#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_B 1048576UL
#define KILO_B 1024UL
#define STR_MAXLENGTH (64 * KILO_B)

long * debug_table;

void show_table(long * table, long n, long m) {
	static const char grays[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
	static const int grayscale = 62;

	if ( n > 1024 || m > 1024) {
		printf("\ntable seems being too big.\n");
		return;
	}
	// show DP table
	printf("\ntable contents:\n");
	for(long r = 0; r < m; r++) {
		for (long c = 0; c < n; c++) {
			//printf("%c", grays[max(0,61 - (int)((table[m*c+r]/(float)(n))*grayscale))] );
			printf("%3ld ", table[m*c+r]);
		}
		printf("\n");
		fflush(stdout);
	}
	printf("\n\n");
	fflush(stdout);
}

long compare_table(long * t0, long * t1, long n, long m) {
	long c, r;
	long count = 0;
	for(c = 0; c < n; c++) {
		for(r = 0; r < m; r++) {
			if( t0[m*c+r] != t1[m*c+r] ) {
				count ++;
				printf("different @ %ld, %ld\n", c, r);
			}
		}
	}
	if ( count > 0 )
		printf("%ld different elements in table.\n", count);
	printf("\n");
	return count;
}

int getargs(const int argc, const char * argv[], char * text, char * patt, long * n, long *m) {
	if ( argc != 3 )
		return EXIT_FAILURE;

	text[STR_MAXLENGTH-1] = 0;
	patt[STR_MAXLENGTH-1] = 0;

	if ( textfromfile(argv[1], STR_MAXLENGTH, text) != 0
		|| textfromfile(argv[2], STR_MAXLENGTH, patt) != 0 ) {
		return EXIT_FAILURE;
	}
	*n = (text[STR_MAXLENGTH-1] == 0? strlen(text) : STR_MAXLENGTH);
	*m = (patt[STR_MAXLENGTH-1] == 0? strlen(patt) : STR_MAXLENGTH);
	if ( *n < *m ) {
		char * tmp = text;
		text = patt;
		patt = tmp;
		long t = *n;
		*n = *m;
		*m = t;
	}

	if ( *n < 1000 && *m < 1000 )
		fprintf(stdout, "Input: %s \n(%lu), \n%s \n(%lu)\n\n", text, *n, patt, *m);
	else
		fprintf(stdout, "Input: (%lu), (%lu)\n\n", *n, *m);
	fflush(stdout);

	return 0;
}

int main (int argc, const char * argv[]) {
	char * text, *patt;
	long * table;
	long m, n;
	long d;
	
	text = malloc(sizeof(char)*STR_MAXLENGTH);
	patt = malloc(sizeof(char)*STR_MAXLENGTH);
	if ( text == NULL || patt == NULL ) {
		fprintf(stderr, "malloc error.\n");
		fflush(stderr);
		goto exit_error;
	}

	if ( getargs(argc, argv, text, patt, &n, &m) != 0 )
		goto exit_error;

	table = (long*) malloc(sizeof(long)*m*n);

	stopwatch sw;
	stopwatch_start(&sw);

	d = dp_edist(table, text, n, patt, m);

	stopwatch_stop(&sw);

	printf("Edit distance (by Pure DP): %lu\n", d);
	printf("%lu sec %lu milli sec.\n", stopwatch_secs(&sw), stopwatch_millis(&sw));
	printf("\n");

#ifdef DEBUG_TABLE
	show_table(table, n, m);

	debug_table = (long*) malloc(sizeof(long)*m*n);
#endif

	fprintf(stdout, "computing edit distance by Waving DP.\n");
	fflush(stdout);

	stopwatch_start(&sw);

	long * frame = (long*)malloc(sizeof(long)*ceilpow2(m+n+1));
	wv_setframe(frame, text, n, patt, m);
	for(int i = 0; i < ceilpow2(m+n+1); i++)
		printf("%ld, ",frame[i]);
	printf("\n");

	d = wv_edist(frame, text, n, patt, m);
	free(frame);
	stopwatch_stop(&sw);

	printf("Edit distance (by Weaving DP): %ld\n", d);
	printf("%ld sec %ld milli sec.\n", stopwatch_secs(&sw), stopwatch_millis(&sw));

#ifdef DEBUG_TABLE
	show_table(debug_table, n, m);

	if ( compare_table(debug_table, table, n, m) != 0) {
		printf("table compare failed.\n");
	} else {
		printf("two tables are identical.\n");
	}
	free(debug_table);
#endif
	free(table);

exit_error:
	free(text);
	free(patt);

    return 0;
}

