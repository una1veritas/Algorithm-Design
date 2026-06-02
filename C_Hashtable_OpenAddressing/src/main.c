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
	OAHashtable * htbl;
	long tblsize = 11;
	datatype entry[] = {
			{ "242G1022", "Takako"},
			{ "242G1103", "Hiroto"},
			{ "242G1201", "Tomoya"},
			{ "242G1039", "Fuyumi"},
			{ "242G1209", "Shouichi"},
			{ "242G1376", "Akio"},
			{ "242G1211", "Natsu"},
			{ "242G1371", "Haruyo"},
			{ "242G1183", "Shiori"},
			//{ "", "" },
	};
	int n = sizeof(entry)/sizeof(datatype);
	printf("entry size = %u\n", n);
	//datatype d[n];
	int i = 0; //, argix = 0;
	while (i < n) {
		//strncpy(d[i].id, entry[argix], 8);
		//++argix;
		//strncpy(d[i].name, entry[argix], 32);
		//d[i].name[31] = 0;
		//++argix;
		printOn(stdout, &entry[i]);
		++i;
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");


	printf("Hash table size = %ld\n", tblsize);
	htbl = OAHashtable_allocate(tblsize);
	for(long i = 0; i < n; ++i)
		OAHashtable_add(htbl, &entry[i]);

	printf("\nthe number of entries = %d\n", htbl->count);
	OAHashtable_fprintf(stdout, htbl, "%s, ");

	fputs("\nremove element ", stdout);
	printOn(stdout, &entry[4]);
	fputs("\n", stdout);
	OAHashtable_remove(htbl, &entry[4]);
	OAHashtable_fprintf(stdout, htbl, "%s, ");

	OAHashtable_free(htbl);
	printf("\nfinished.\n");
	return EXIT_SUCCESS;
}
