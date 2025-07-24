//============================================================================
// Name        : StringConverter.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <string.h>

int main() {
	char sid[] = "246E1024";
	char id[7];
	for(int i = 0; i < 6; ++i)
		id[i] = sid[7 - i];
	id[6] = (char) 0;
	id[0] += 17;
	printf("%s\n", id);
	return 0;
}
