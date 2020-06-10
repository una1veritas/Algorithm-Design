#include <stdio.h>

int main() {
  char s[] = "THIS IS A PEN.";
  printf("%0x\n", *((int *) s));

  return 0;
}
