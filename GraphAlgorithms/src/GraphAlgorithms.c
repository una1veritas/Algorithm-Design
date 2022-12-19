/*
 ============================================================================
 Name        : GraphAlgorithms.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	char * vstr = argv[1];
	char * estr = argv[2];
	printf("'%s'\n", vstr);
	printf("'%s'\n", estr);

	char buff[1024];
	for(char * ptr = vstr; ; ) {
		if ( sscanf(ptr, "%1023[^, \n]s", buff) == 0 )
			break;
		printf("token = '%s' length = %lu\n", buff, strlen(buff));
		ptr += strlen(buff);
		sscanf(ptr, "%1023[, \n]s", buff);
		if ( *ptr == 0 ) {
			printf("ptr reached at the end.\n");
			break;
		}
		ptr += strlen(buff);
		//printf("%s\n", buff);
	}
	return EXIT_SUCCESS;
}
