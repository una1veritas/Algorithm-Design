/*
 * TowerOfHanoi.c by Sin Shimozono
 * download from github una1veritas/Algorithm-Design/RecursionSample/
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int count;
	int disks[32];
} DiskStack;

void show_stacks(DiskStack stacks[]);

/*
 * move the disk on top of disks in `from' to 'to'.
 */
long Hanoi_move(DiskStack stacks[], int id_from, int id_to) {
	// pop the top disk
	int topdisk = stacks[id_from].disks[stacks[id_from].count-1];
	stacks[id_from].disks[stacks[id_from].count-1] = 0;
	--stacks[id_from].count;
	// push the disk on top
	stacks[id_to].disks[stacks[id_to].count] = topdisk;
	++stacks[id_to].count;
	show_stacks(stacks);
	return 1;
}

/*
 * move num disks from the top of the `src' rod to the `dst' rod.
 */
long Hanoi(DiskStack stacks[], int num, int id_src, int id_work, int id_dst) {
	long moves;
	if ( num == 1 ) {
		return Hanoi_move(stacks, id_src, id_dst);
	}
	moves = Hanoi(stacks, num-1, id_src, id_dst, id_work);
	moves += Hanoi_move(stacks, id_src, id_dst);
	moves += Hanoi(stacks, num-1, id_work, id_src, id_dst);
	return moves;
}
/*
int main(int argc, char * argv[]) {
	int n = (argc >= 2 ? atoi(argv[1]) : 3);
	int moves;
	DiskStack stacks[3] = {{0, {0}}, {0, {0}}, {0, {0}}};
	if (n > 31) n = 31;
	printf("Tower with %d disks.\n", n);
	stacks[0].count = n;
	for(int i = 0; i <= n; ++i) {
		stacks[0].disks[i] = n - i;
	}
	show_stacks(stacks);
	moves = Hanoi(stacks, stacks[0].count, 0, 1, 2);
	printf("%d moves.\n", moves);
	return EXIT_SUCCESS;
}
*/
/*
 * Show disks on the rods.
 */
void show_stacks(DiskStack rods[]) {
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
