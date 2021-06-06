
int main(int argc, char **argv) {
	char str[strlen(argv[1])];
	char * ptr;
	const char delims = " ,;:";
	strcpy(str, argv[1]);
	for(ptr = strtok(str, delims); ptr != NULL;
			ptr = strtok(NULL, delims) ) {
		printf("%s\n", ptr);
	}
	return 0;
}
