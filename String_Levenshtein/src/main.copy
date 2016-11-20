#include <stdio.h>
#include <string.h>

#include "stopwatch.h"

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
	char * s = (char *) argv[1], * t = (char *) argv[2];
	int m = strlen(s), n = strlen(t);
	int d;
	
	stopwatch sw;

	printf("Input: %s (%d), %s (%d)\n", s, m, t, n);
	
	stopwatch_start(&sw);
	//d = r_edist(s, m, t, n);
	stopwatch_stop(&sw);
	printf("Edit distance (by recursion): %d\n", d);
	printf("%lu milli %lu micro secs.\n", stopwatch_millis(&sw), stopwatch_micros(&sw));
	printf("\n");

	stopwatch_start(&sw);
	d = dp_edist(s, m, t, n);
	stopwatch_stop(&sw);
	printf("Edit distance (by DP): %d\n", d);
	printf("%lu milli %lu micro secs.\n", stopwatch_millis(&sw), stopwatch_micros(&sw));
	
    return 0;
}
