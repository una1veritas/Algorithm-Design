/*
 ============================================================================
 Name        : getargs.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int getargs(const int argc, const char * argv[]);

int main(const int argc, const char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	getargs(argc, argv);

	return EXIT_SUCCESS;
}


int getargs(const int argc, const char * argv[]) {
	int argcnt;
	char ** argptr;
	char *argstr;
	char optname[16];
	enum {
		STR,
		OPT,
	} nextopt;
	enum {
		HUH,
		DEBUG_TABLE,
	} optchoice;

	nextopt = STR;
	for ( argcnt = argc, argptr = argv; argcnt > 0; argcnt--, argptr++ ) {
		argstr = *argptr;
		if ( nextopt == STR && argstr[0] == '-' ) {
			printf("option!\n");
			strcpy(optname, argstr+1);
			printf("name = %s\n", optname);
			if (strcmp(optname, "huh") == 0) {
				optchoice = HUH;
				nextopt = OPT;
			} else if ( strcmp(optname, "g") == 0) {
				optchoice = DEBUG_TABLE;
				nextopt = STR;
			}
		} else if ( nextopt == STR ) {
			printf("%d: %s\n", argcnt, argstr);
		} else if ( nextopt == OPT ) {
			printf("value for option: %s\n", argstr);
			nextopt = STR;
		}
	}

	return 0;
}
