#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  if (argc == 1) {
    return EXIT_FAILURE;
  }
  for(char ** p = &argv[1]; *p; ++p) {
    printf("%s = %d\n", *p, *((int*)*p));
  }

  return EXIT_SUCCESS;
}

 
