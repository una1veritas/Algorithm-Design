#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char id[4];
	char name[32];
} data;

/* 比較関数: lessthaneq(a, b) は a <= b なら 1, a > b なら 0 */
int lessthaneq(const data * d1, const data * d2) {
     int res = strncmp(d1->id, d2->id, 4);
     return (res == 0) ? 1 : (res < 0 ? 1 : 0);
}

/* down_to_leaf, build_heap, heap_sort 等をここに作る.    */
/* 関数のプロトタイプ宣言をして別の場所, 順番で作ってもかまわない */

/* 添え字列のソートと比較関数の使用の参考: シェルソート  */
/* この関数は解答にいれないでください. */
void shell_sort(data d[], int idx[], int n) {
	int t, j;
	for(int w = n>>1; w > 0; w >>= 1) {
		for(int i = w; i < n; ++i) { /* w 飛び列のインサーションソート */
			t = idx[i];
			for (j = i; j >= w && !lessthaneq(&d[idx[j - w]], &d[t]); j -= w)
				idx[j] = idx[j - w];
			idx[j] = t;
			/* データ列 d を直接入れ替えすると, 重くなる可能性がある */
		}
	}
}

int main(const int argc, const char *argv[]) {
     data db[argc/2];
     int n = 0, i;
     for (i = 1; i+1 < argc; ) {
    	 strncpy(db[n].id, argv[i], 4);
    	 db[n].id[3] = 0;
    	 strncpy(db[n].name, argv[i+1], 31);
    	 i += 2;
    	 db[n].name[31] = '\0';
    	 n += 1;
     }
     int index[n]; /* int * index = (int*) malloc(sizeof(int)*n); */
     printf("input: \n");
     for (int i = 0; i < n; ++i) {
    	 index[i] = i;
          printf("%s, %s\n", db[index[i]].id, db[index[i]].name);
     }
     printf("\n");

     /*
      * dbase[index[0]], dbase[index[1]],..., dbase[index[n-1]] が
      * id でソートされるように heap_sort を作る
      * */
     //heap_sort(dbase, index, n);
     shell_sort(db, index, n);

     printf("after sorting:\n");
     for (int i = 0; i < n; ++i) {
         printf("%s, %s\n", db[index[i]].id, db[index[i]].name);
     }
     printf("\n");

     return 0;
}
