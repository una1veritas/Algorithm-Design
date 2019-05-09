/*
 * TowerOfHanoi.c by Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int count;
	int disks[10];
} Rod;
void Rods_show(Rod rods[]);

/*
 * move the disk on top of disks in `from' to 'to'.
 */
long Hanoi_move(Rod rods[], int id_from, int id_to) {
	// pop the top disk
	int topdisk = rods[id_from].disks[rods[id_from].count-1];
	rods[id_from].disks[rods[id_from].count-1] = 0;
	--rods[id_from].count;
	// push the disk on top
	rods[id_to].disks[rods[id_to].count] = topdisk;
	++rods[id_to].count;
	Rods_show(rods);
	return 1;
}

/*
 * move num disks from the top of the `src' rod to the `dst' rod.
 */
long Hanoi(Rod rods[], int num, int id_src, int id_work, int id_dst) {
	long moves;
	if ( num == 1 ) {
		return Hanoi_move(rods, id_src, id_dst);
	}
	moves = Hanoi(rods, num-1, id_src, id_dst, id_work);
	moves += Hanoi_move(rods, id_src, id_dst);
	moves += Hanoi(rods, num-1, id_work, id_src, id_dst);
	return moves;
}

int main(int argc, char * argv[]) {
	int n = (argc >= 2 ? atoi(argv[1]) : 3);
	int moves;
	Rod rods[3] = {{0}, {0}, {0}};
	if (n > 10) n = 10;
	printf("Tower with %d disks.\n", n);
	rods[0].count = n;
	for(int i = 0; i <= n; ++i) {
		rods[0].disks[i] = n - i;
	}
	Rods_show(rods);
	moves = Hanoi(rods, rods[0].count, 0, 1, 2);
	printf("%d moves.\n", moves);
	return EXIT_SUCCESS;
}

/*
 * Show disks on the rods.
 */
void Rods_show(Rod rods[]) {
	for(int r = 0; r < 3 ; ++r) {
		printf("[");
		for(int i = 0; i < rods[r].count; ++i) {
			if ( rods[r].disks[i] == 0)
				break;
			printf("%d", rods[r].disks[i]);
			if ( i + 1 < rods[r].count )
				printf(" ");
		}
		printf("]\n");
	}
	printf("----------\n");
}
