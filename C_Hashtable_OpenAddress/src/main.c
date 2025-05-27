/*
 ============================================================================
 Name        : C_Hashtable_OpenAddress.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datatype.h"
#include "OAHashtable.h"

int main(const int argc, const char * argv[]) {
	OAHashtable * tbl;
	long tblsize = 17;
	char * entry[] = {
			"242G1022", "Takako",
			"242G1103", "Hiroto",
			"242G1209", "Shouichi",
			"242G1376", "Aki",
			"242G1183", "Shiori",
	};
	printf("entry size = %d\n", sizeof(entry));
	int n = 5;
	/*
	int n = (argc - 1)>>1;
	*/
	datatype d[n];
	int i = 0, argix = 0;
	while (i < n) {
		strncpy(d[i].id, entry[argix], 8);
		++argix;
		strncpy(d[i].name, entry[argix], 32);
		d[i].name[31] = 0;
		++argix;
		++i;
	}

	printf("Hash table size = %ld\n", tblsize);
	tbl = allocate_OAHashtable(tblsize);
	for(long i = 0; i < n; ++i)
		OAHashtable_add(tbl, &d[i]);

	printf("the number of entries = %d\n", tbl->elemcount);
	OAHashtable_fprintf(stdout, tbl, "%s, ");

	free_OAHashtable(tbl);
	printf("\nfinished.\n");
	return EXIT_SUCCESS;
}
