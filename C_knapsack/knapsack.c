#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "knapsack.h"

// O(2^n) 時間，O(n^2) スペースのアルゴリズム。num は品物の数。
// spot 番目以降の品物から、予算 budget 円で買う／買わないのベストな選択を buyornot に記録する。
// ただし，buyornot は spot + 1 番目以降の品物についてのみのサイズを確保し記録する。オーダーはかわらないがスペースの節約のため。

int best_pruning(int pricelist[], int num, int budget, bool buyornot[]) {
	return best_pruning_recursive(pricelist, num, 0, budget, buyornot);
}

int best_pruning_recursive(int pricelist[], int num, int spot, int budget, bool buyornot[]) {
	int sum_skip, sum_buy;
	if ( spot >= num ) {
		return 0;
	}

	// 予算 budget 円での買わない／買えない場合の spot + 1 以降のベストな購入リストを探索する。

	// buyornot[1] が thinking[0] に対応する。
	bool thinking[num - spot - 1];
    // 買わない場合の探索。budget はそのまま。
	sum_skip = best_pruning_recursive(pricelist, num, spot+1, budget, thinking);

	// みつけた spot + 1 以降のベストな購入リストを buyornot にコピーする。
	// 買う場合の計算で，thinking の spot + 1 以降が破壊されるため。
	for (int i = 0; i < num - spot - 1; ++i) {
		buyornot[1+i] = thinking[i];
	}

	// 買えない場合。spot + 1 以降はベストな選択がコピー済み。
	if ( pricelist[spot] > budget) {
		// spot 番目は買えない。
		buyornot[0] = false;
		return sum_skip;
	}

    // 買う場合をためす。
	sum_buy = pricelist[spot] + best_pruning_recursive(pricelist, num, spot + 1, budget - pricelist[spot], thinking);
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

int main (int argc, const char * argv[]) {
	// Set up the input.
	int budget = atoi(argv[1]);
	int number = argc - 2;
	int prices[number];
	bool buyornot[number + 1];
	for (int i = 0; i < number; ++i) {
		prices[i] = atoi(argv[2+i]);
	}
	prices[number] = 0; // sentinel
	
	// Show the input.
	printf("%d yen, the following %d items:\n", budget, number);
	for (int i = 0; i < number; ++i) {
		printf("%d, ", prices[i]);
	}
	printf("\n\n");

	printf("買うの？買わないの？\n");
	int totalPrice = best_pruning(prices, number, budget, buyornot);
	printf("buy items: ");
	for (int i = 0; i < number; ++i) {
		if ( buyornot[i] )
			printf("[%d] %d, ", i, prices[i]);
	}
	printf("\ntotally %d yen.\n", totalPrice);

	return 0;
}
