/*
 ============================================================================
 Name        : csplit.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char ** csplit(char * str, const char delims[]) {
	char buf[strlen(str)];
	strcpy(buf, str);
	int count = 0;
    for (char * tp = strtok(buf, delims);
    		tp != NULL;
            tp = strtok(NULL, delims) ) {
    	count++;
    }
    if (count == 0)
    	return (char**)NULL;
    char ** ptrs = (char**) malloc(sizeof(char*) * (count+1));
    int i = 0;
    for (char * tp = strtok(str, delims); ;
            tp = strtok(NULL, delims), ++i ) {
    	ptrs[i] = tp;
    	if (tp == NULL)
    		break;

    }
    return ptrs;
}

int main(const int argc, const char **argv) {
    const char delims[] = " ,?;:()";
    char strbuf[strlen(argv[1])];
    strcpy(strbuf, argv[1]);
    char ** tokens = csplit(strbuf, delims);
    for (int i = 0; tokens[i]; ++i) {
    	printf("%s, %d\n", tokens[i], atoi(tokens[i]));
    }
    free(tokens);
    return EXIT_SUCCESS;
}
