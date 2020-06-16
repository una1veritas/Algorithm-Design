#include <stdio.h>
int main(int argc, char * argv[]) {
  if (argc == 1) {
    return 1;
  }
  int sum = 0;
  for(char * p = argv[1]; *p; ++p) {
    sum += *p;
  }
  printf("sum = %d\n",sum);

  return 0;
}

 
