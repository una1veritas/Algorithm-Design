//============================================================================
// Name        : DownwardCompatibility.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
/* #include <stdio.h> でもよい */

int main(int argc, char * argv[]) {
	for(int i = 0; i < argc; ++i) {
		printf("%s, \n", argv[i]);
	}
	return 0;
}
