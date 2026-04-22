#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "knapsack.h"

// 入力： prices 商品の価格リスト, nsize リストの先頭から購入を検討する商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額, cart はベストな購入で i 番目の商品が選ばれているかを格納
int best_enumeration(int prices[], int budget, bool buyornot[]) {
	int num;
	//商品の数を数える
	for (num = 0; prices[num] != 0; ++num) {}

	if ( num == 0 ) {
		return 0;
	}

	int sum, best;
	int item;

	bool subset[num + 1]; 	// 計算に使う仮の購入リスト．buyornot はサイズが num で buyornot[num] が使えるかどうか保証されないため．
	for(int i = 0; i < num + 1; ++i)
		subset[i] = false;  	// 仮の購入リストを空集合に初期化

	best = 0;
	for(; subset[num] == false ;) {
		sum = 0;
		// 購入リスト subset での合計金額を求める
		for(item = 0; item < num && sum <= budget; ++item) {
			if (subset[item] != false )
				sum += prices[item];
		}
		// 合計が budget 以下かつ best より大きい場合 buyornot を更新する
		if (best < sum && sum <= budget ) {
			best = sum;
			// 現時点での最もよい購入リストとして subset の組合せを保存
			for(int i = 0; i < num; ++i)
				buyornot[i] = subset[i];
		}

		// 部分集合 subset を二進数（添字 0 側が下位）と見なしてインクリメントする
		for(item = 0; item < num + 1; ++item) {
			if ( subset[item] == false ) {
				subset[item] = true;
				break;
			} else {
				subset[item] = false;
			}
		}
	}

	return best;
}

// 価格リストの先頭（呼び出し側からは価格リストの途中へのポインタ）以降，終端値 0 までの品物から，
// 予算 budget 円で買う／買わないのベストな選択を購入リスト buyornot に記録する。
// buyornot は 1 番目以降の品物についてのみのサイズを確保し記録する。
// 0 番目の選択は直接 buyornot[0] に記録する。
// O(2^n) 時間，O(n^2) スペースのアルゴリズム。

int best_pruning(int pricelist[], int budget, bool buyornot[]) {
	int sum_skip, sum_buy;

	if ( pricelist[0] == 0) {
		// 価格リスト終端
		return 0;
	}

	// thinking の大きさを決めるため（にのみ） pricelist の要素数 num を求める。
	int num;
	for (num = 0; pricelist[num] != 0; ++num) {	}
	// buyornot[1] が thinking[0] に対応する。
	bool thinking[num - 1];	// 関数内のみ

    // 買わない場合の探索。budget はそのまま。
	sum_skip = best_pruning(pricelist + 1, budget, thinking);

	// みつけた spot + 1 以降のベストな購入リストを buyornot にコピーする。
	// 買う場合の計算で，thinking の spot + 1 以降が破壊されるため。
	for (int i = 0; i < num; ++i) {
		buyornot[1+i] = thinking[i];
	}

	// 買えない場合。spot + 1 以降はベストな選択がコピー済み。
	if ( pricelist[0] > budget) {
		// 0 番目は買えない。
		buyornot[0] = false;
		return sum_skip;
	}

    // 買う場合をためす。
	sum_buy = pricelist[0] + best_pruning(pricelist+1, budget - pricelist[0], thinking);
	if (sum_buy > sum_skip) {
		for (int i = 0; i < num; ++i) {
			buyornot[1+i] = thinking[i];
		}
		// 買うという選択。
		buyornot[0] = true;
		return sum_buy;
	}
	// 買わないほうがよかったという結論。
	buyornot[0] = false;
	return sum_skip;
}

// 300 15, 20, 49, 52, 19, 18, 68, 38, 38, 38, 55, 39, 108, 103, 18, 41, 44, 45, 78, 78, 58, 58, 68, 58, 128,
// 300 -num=41 300 17, 17, 17, 33, 17, 17, 17, 322, 44, 54, 22, 22, 22, 76, 171, 160, 81, 108, 171, 204, 54, 150, 74, 54, 150, 106, 119, 33, 76, 38, 33, 33, 22, 27, 23, 87, 12, 33, 17, 65, 33

int main (int argc, const char * argv[]) {
	struct timespec start, stop;
	long secs, nanos;
	bool do_enumeration = false; //, do_pruning = false;

	int budget = 0, number = 0;
	if ( argc < 3 ) {
		printf("usage: command [-num=xx] budget price_1 price_2 ...\n");
		return EXIT_FAILURE;
	}
	int argix = 1;
	while (argix < argc) {
		if ( strncmp(argv[argix], "-num=", 5) == 0 ) {
			number = atoi(argv[argix] + 5);
			++argix;
		} else if ( strncmp(argv[argix], "-enum", 5) == 0 ) {
			do_enumeration = true;
			++argix;
		} else if (budget == 0) {
			budget = atoi(argv[argix]);
			++argix;
			break;
		}
	}
	// Set up the input.
	if (number <= 0)
		number = argc - argix - 1;
	int prices[number];
	int totalPrice;
	bool buyornot[number + 1];
	for (int i = 0; i < number; ++i) {
		prices[i] = atoi(argv[argix+i]);
	}
	prices[number] = 0; // sentinel
	
	// Show the input.
	printf("%d yen, the following %d items:\n", budget, number);
	for (int i = 0; i < number; ++i) {
		printf("%d, ", prices[i]);
	}
	printf("\n\n");

	if ( do_enumeration ) {
		printf("買うの？買わないの？\n");
		timespec_get(&start, TIME_UTC); 	// 計測開始
		totalPrice = best_enumeration(prices, budget, buyornot);
		timespec_get(&stop, TIME_UTC);		// 計測終了
		secs = stop.tv_sec - start.tv_sec; // swatch = clock() - swatch;
		nanos = stop.tv_nsec - start.tv_nsec;
		printf("全探索: %.6f sec.\n", (double) secs + ((double) nanos/1e9) );
		printf("buy items: ");
		for (int i = 0; i < number; ++i) {
			if ( buyornot[i] )
				printf("[%d] %d, ", i, prices[i]);
		}
		printf("\ntotally %d yen.\n\n", totalPrice);
	}

	printf("買うの？買わないの？\n");
	timespec_get(&start, TIME_UTC); 	// 計測開始
	totalPrice = best_pruning(prices, budget, buyornot);
	timespec_get(&stop, TIME_UTC);		// 計測終了
	secs = stop.tv_sec - start.tv_sec; // swatch = clock() - swatch;
	nanos = stop.tv_nsec - start.tv_nsec;
	printf("全探索枝刈り: %.6f sec.\n", (double) secs + ((double) nanos/1e9) );
	printf("buy items: ");
	for (int i = 0; i < number; ++i) {
		if ( buyornot[i] )
			printf("[%d] %d, ", i, prices[i]);
	}
	printf("\ntotally %d yen.\n\n", totalPrice);

	return 0;
}
