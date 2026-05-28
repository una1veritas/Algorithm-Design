#include <stdio.h>
#include <string.h>

#define NAME_LENGTH_LIMIT 32

typedef struct Data {
	unsigned int id;
	char name[NAME_LENGTH_LIMIT];
} Data;

int order_byname(const void * a, const void * b) {
	Data * d0 = (Data *) a, *d1 = (Data *) b;
	if ( strncmp(d0->name, d1->name, NAME_LENGTH_LIMIT) >= 0 )
		return 1;
	return 0;
}

int main(const int argc, char *argv[]) {
      long n = argc - 1;
      Data data[n];
      for (int i = 0; i < n; ++i) {
    	  data[i].id = 1 + i;
          strncpy(data[i].name, argv[1 + i], NAME_LENGTH_LIMIT);
          printf("(%u, %s), ", data[i].id, data[i].name);
      }
      printf("\n\n");
      qsort(data, n, sizeof(data[0]), order_byname);
      for (int i = 0; i < n; ++i) {
          printf("(%u, %s), ", data[i].id, data[i].name);
     }
      printf("\n\n");
      return 0;
}

/*
 * ./a.out Robert Thomas Elizabeth Hellen Meg
 *
 * (1, Robert), (2, Thomas), (3, Elizabeth), (4, Hellen), (5, Meg),
 *
 * (3, Elizabeth), (4, Hellen), (5, Meg), (1, Robert), (2, Thomas),
 *
 */
