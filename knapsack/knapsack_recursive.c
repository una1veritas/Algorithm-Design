#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から購入を検討する商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額, cart はベストな購入で i 番目の商品が選ばれているかを格納
int knapsack_recursive(const int prices[], const int nsize, const int budget, char cart[]) {
	if ( nsize == 0 ) {
		cart[0] = 0;
		return 0;
	}

	int sum0, sum1;   	// prices[nsize - 1] を購入しない場合と購入した場合それぞれの合計金額
	char cart0[nsize];	// 購入しない場合の nsize 番目までについてのベストな購入リスト
	char cart1[nsize];	// 購入する場合の nsize 番目までについてのベストな購入リスト

	// 検討対象は nsize 個で (prices[0], ... , prices[nsize-1])
	// prices[nsize-1] を購入しない場合
	sum0 = knapsack_recursive(prices, nsize - 1, budget, cart0);

	if ( prices[nsize - 1] <= budget) {
		// prices[nsze-1] を購入する場合
		sum1 = prices[nsize - 1] + knapsack_recursive(prices, nsize - 1, budget - prices[nsize-1], cart1);
		if ( sum1 > sum0 ) {
			// 購入すると合計額がより大きくなる場合, cart に cart1[0],...,cart1[nsize-2] をコピー
			for(int i = 0; i < nsize - 1; ++i)
				cart[i] = cart1[i];
			cart[nsize - 1] = 1;  //購入すると決定
			return sum1;
		}
	}
	for(int i = 0; i < nsize - 1; ++i) {
		cart[i] = cart0[i];
	}
	cart[nsize - 1] = 0;	//購入しないと決定
	return sum0;
}
