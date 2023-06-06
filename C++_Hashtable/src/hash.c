#include <stdio.h>

unsigned int hash(char idstr[]) {
     unsigned int hv = 0;
     for(int i = 4; i > 0; --i) {
          hv <<= 7;
          hv += idstr[i] ^ idstr[3+i];
     }
     return hv;
}

int main(int argc, char * argv[]) {
  printf("%u\n",hash(argv[1]));
  return 0;
}
