#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_B 1048576UL
#define KILO_B 1024UL
#define STR_MAXLENGTH (32 * KILO_B)

int r_edist(char s[], int m, char t[], int n) {
	int a, b, c;
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

unsigned long dp_edist(char t[], unsigned long n, char p[], unsigned long m) {
	unsigned long * dist;
	unsigned long result = 0;
	unsigned long i, j, ins, del, repl;
	
	dist = (unsigned long *) malloc(sizeof(unsigned long)*(m+1)*(n+1));
	if ( dist == NULL )
		return 0;

	// initialize
	for(i = 0; i < n+1; i++)
		dist[(i)] = i;
	for(i = 0; i < m+1; i++) 
		dist[((n+1)*i+0)] = i;
	
	//table calcuration
	for(i = 1; i < n+1; i++) { // column
		for (j = 1; j < m+1; j++) {  // row
			ins = dist[(i-1)+(n+1)*j]+1;
			del = dist[i + (n+1)*(j-1)]+1;
			repl = dist[(i-1) + (n+1)*(j-1)] + (t[i-1] == p[j-1] ? 0 : 1);
			dist[i + (n+1)*j] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
		}
	}
	// show DP table 
	/*
	for(i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) { 
			printf("%d\t", d[i][j]);
		}
		printf("\n");
	}
	 */
	result = dist[n + (n+1)* m];
	free(dist);
	return result;
}

int main (int argc, const char * argv[]) {
	char * text, *patt;
	unsigned long m, n;
	unsigned long d;
	
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
		printf("Input: %s (%lu), %s (%lu)\n\n", text, n, patt, m);
	else
		printf("Input: (%lu), (%lu)\n\n", n, m);
	
	stopwatch_start(&sw);
	if ( n > 100 || m > 100 ) {
		printf("Skip recursion version.\n");
	} else {
		d = r_edist(text, n, patt, m);
		stopwatch_stop(&sw);
		printf("Edit distance (by recursion): %lu\n", d);
		printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	}
	printf("\n");

	stopwatch_start(&sw);
	d = dp_edist(text, n, patt, m);
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %lu\n", d);
	printf("%lu sec %lu milli %lu micros.\n", stopwatch_secs(&sw), stopwatch_millis(&sw), stopwatch_micros(&sw));
	
exit_error:
	free(text);
	free(patt);

    return 0;
}

