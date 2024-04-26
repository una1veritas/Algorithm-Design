#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から検討対象とする商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額,
//       cart はベストな購入で商品 i が選ばれているかどうかを格納する長さ nsize （以上の）列
int knapsack_recursive(const int prices[], const int nsize, const int budget, char cart[]) {
	if ( nsize == 0 )
		return 0;

	int sum0, sum1;   	// prices[nsize - 1] を購入しない場合と購入した場合それぞれの合計金額
	char cart0[nsize];	// 購入しない場合の nsize 番目までについてのベストな購入リスト
	char cart1[nsize];	// 購入する場合の nsize 番目までについてのベストな購入リスト

	// 検討対象は nsize 個で (prices[0], ... , prices[nsize - 1])
	// 最後の商品 nsize -1 価格 prices[nsize - 1] を購入しない場合
	cart0[nsize - 1] = 0;
	sum0 = knapsack_recursive(prices, nsize - 1, budget, cart0);

	if ( prices[nsize - 1] <= budget) {
		// nsize -1 を購入できる，かつ実際に prices[nsize - 1] を購入する場合
		cart1[nsize - 1] = 1;
		sum1 = prices[nsize - 1] +
				knapsack_recursive(prices, nsize - 1, budget - prices[nsize - 1], cart1);
		if ( sum1 > sum0 ) {
			// 購入すると合計額がより大きくなる場合, cart に cart1[0],...,cart1[nsize-2] をコピー
			for(int i = 0; i < nsize; ++i)
				cart[i] = cart1[i];
			return sum1;
		}
	}
	//購入しないと決定し cart に cart0[0],...,cart0[nsize-1] をコピー
	for(int i = 0; i < nsize; ++i) {
		cart[i] = cart0[i];
	}
	return sum0;
}
