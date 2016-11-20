#include <stdio.h>
#include <string.h>

#include "stopwatch.h"
#include "textfromfile.h"

#define MEGA_BIN 1048576UL
#define KILO_BIN 1024UL
#define STR_MAXLENGTH (4 * MEGA_BIN)

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

int dp_edist(char s[], int m, char t[], int n) {
	int dist[m+1][n+1];
	int i, j, ins, del, repl;
	
	for(i = 0; i < m+1; i++) 
		dist[i][0] = i;
	for(j = 0; j < n+1; j++) 
		dist[0][j] = j;
	
	for(i = 1; i < m+1; i++) {
		for (j = 1; j < n+1; j++) {
			ins = dist[i-1][j]+1;
			del = dist[i][j-1]+1;
			repl = dist[i-1][j-1] + (s[i-1] == t[j-1] ? 0 : 1);
			dist[i][j] = ins < del ? (ins < repl ? ins : repl) : (del < repl ? del : repl);
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
	return dist[m][n];
}

int main (int argc, const char * argv[]) {
	char * text, *patt;
	unsigned long m, n;
	unsigned long d;
	
	stopwatch sw;

	if ( argc != 3 )
		return EXIT_FAILURE;

	text = malloc(sizeof(char)*STR_MAXLENGTH);
	patt = malloc(sizeof(char)*STR_MAXLENGTH);

	if ( textfromfile(argv[1], STR_MAXLENGTH, text) != 0
		|| textfromfile(argv[2], STR_MAXLENGTH, patt) != 0 ) {
		goto exit_error;
	}
	n = (text[STR_MAXLENGTH-1] == 0? strlen(text) : STR_MAXLENGTH);
	m = (patt[STR_MAXLENGTH-1] == 0? strlen(patt) : STR_MAXLENGTH);

	if ( n < 1000 && m < 1000 )
		printf("Input: %s (%lu), %s (%lu)\n", text, n, patt, m);
	
	stopwatch_start(&sw);
	d = 0;//d = r_edist(s, m, t, n);
	stopwatch_stop(&sw);
	printf("Edit distance (by recursion): %lu\n", d);
	printf("%lu milli %lu micro secs.\n", stopwatch_millis(&sw), stopwatch_micros(&sw));
	printf("\n");

	stopwatch_start(&sw);
	d = dp_edist(text, n, patt, m);
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %lu\n", d);
	printf("%lu milli %lu micro secs.\n", stopwatch_millis(&sw), stopwatch_micros(&sw));
	
exit_error:
	free(text);
	free(patt);

    return 0;
}

