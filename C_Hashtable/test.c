#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  if (argc < 3) {
    return 1;
  }
  long tablesize = atol(argv[1]);
  for(char ** p = argv+2; *p; ++p) {
    long k = atol(*p);
    printf("%4ld to %4ld \n", k, k % tablesize);
  }
  printf("\n");

  return 0;
}

 
