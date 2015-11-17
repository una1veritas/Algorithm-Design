/*
 ============================================================================
 Name        : MagicSquare_recursive.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int rsearch(int *, int ,int );

int main(int argc, char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	if ( argc != 2 )
		goto exit_failure;

	int rownum = atoi(argv[1]);

	printf("rownum = %d\n", rownum);

	int * square = (int*)malloc(sizeof(int)*rownum*rownum);

	if ( rsearch(square,0,rownum*rownum) ) {

		for(int r = 0; r < rownum; r++) {
			for(int c = 0; c < rownum; c++) {
				printf("|%2d", square[r*rownum+c]);
			}
			printf("|\n");
			for(int c = 0; c < rownum; c++) {
				printf("---");
			}
			printf("\n");
		}
	} else {
		printf("Couldn't find any magic square.\n\n");
	}
	free(square);

	return EXIT_SUCCESS;

	exit_failure:
	return EXIT_FAILURE;
}

int checksquare(int sq[], int size) {
	int row = (int) sqrt((double)size);
	int sum = 0, newsum;
	for(int r = 0; r < row; r++) {
		newsum = 0;
		for(int c = 0; c < row; c++) {
			newsum += sq[r*row+c];
		}
		if ( sum == 0 ) {
			sum = newsum;
		} else {
			if ( sum != newsum )
				return 0;
		}
	}
	for(int c = 0; c < row; c++) {
		newsum = 0;
		for(int r = 0; r < row; r++) {
			newsum += sq[r*row+c];
		}
		if ( sum != newsum )
			return 0;
	}
	return 1;
}

int rsearch(int sq[],int pos,int size) {
	int tbl[size];
	for(int i = 1; i <= size; i++) {
		tbl[i-1] = 0;
	}
	for(int i = 0; i < pos; i++) {
		tbl[sq[i]-1] = 1;
	}
	/*
	for(int i = 1; i <= size; i++) {
		if ( tbl[i-1] == 1 )
		printf("%d, ",i);
	}
	printf("\n");
	*/
	if ( !(pos < size) ) {
		// printf("pos = %d.\n",pos);
		/*
		for(int i = 0; i < size; i++) {
		//		if ( sq[i] != 0)
			printf("%d, ",sq[i]);
		}
		printf("\n");
		*/
		// check
		return checksquare(sq, size);
	}
	int x;
	for(x = 1; x <= size; x++) {
		if ( tbl[x-1] == 0 ) {
			sq[pos] = x;
			if ( rsearch(sq, pos+1, size) )
				return 1;
		}
	}

	return 0; // exhausted.
}
