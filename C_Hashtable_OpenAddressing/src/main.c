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
	long tblsize = 13;
	datatype entry[] = {
			{ "Takako", "Kawazu" },
			{ "Hiroto", "Nishimachi" },
			{ "Fuyumi", "Katsumori" },
			{ "Ryuji", "Tateiwa" },
			{ "Shouichi", "Koubukuro" },
			{ "Akio", "Futase" },
			{ "Natsu", "Takao" },
			{ "Haruyo", "Igisu" },
			{ "Tomoya", "Yokota" },
			{ "Shiori", "Miyamachi" },
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

	datatype remove_data = { "Natsu", "Takao" };
	fputs("\nremove element ", stdout);
	printOn(stdout, &remove_data);
	fputs("\n", stdout);
	OAHashtable_remove(htbl, &remove_data);
	OAHashtable_fprintf(stdout, htbl, "%s, ");

	OAHashtable_free(htbl);
	printf("\nfinished.\n");
	return EXIT_SUCCESS;
}
