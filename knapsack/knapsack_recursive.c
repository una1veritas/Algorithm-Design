#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から検討対象とする商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額,
//       cart はベストな購入で商品 i が選ばれているかどうかを格納する長さ nsize （以上の）列
int knapsack_recursive(const int prices[], const int budget, bool cart[]) {
	int sum0, sum1;   	// prices[nsize - 1] を購入しない場合と購入した場合それぞれの合計金額
	int nsize;
	for (nsize = 0; prices[nsize] ; ++nsize) {}
	bool cart0[nsize];	// 購入しない場合の nsize 番目までについてのベストな購入リスト
	bool cart1[nsize];	// 購入する場合の nsize 番目までについてのベストな購入リスト

	// price 列の終端に至った場合
	if ( prices[0] == 0 ) {
		cart0[0] = false;
		return 0;
	}

	// 検討対象は nsize 個で (prices[0], ... , prices[nsize - 1])
	// 最初の商品の価格 prices[0] を購入しない場合
	cart0[0] = false;
	// C では配列とポインタと同じ, +1 は次の要素を先頭とする配列
	sum0 = knapsack_recursive(prices + 1, budget, cart0 + 1);

	if ( prices[0] <= budget ) {
		// prince[0] を購入できる，かつ prices[0] を購入する場合
		cart1[0] = true;
		sum1 = prices[0] + knapsack_recursive(prices + 1, budget - prices[0], cart1 + 1);
		if ( sum1 > sum0 ) {
			// 購入すると合計額がより大きくなる場合, cart に cart1[0],...,cart1[nsize-1] をコピー
			for(int i = 0; i < nsize; ++i)
				cart[i] = cart1[i];
			return sum1;
		}
	}
	//購入しないと決定，cart[0],...,[nsize-1] に cart0[0],...,cart0[nsize-1] をコピー
	for(int i = 0; i < nsize; ++i) {
		cart[i] = cart0[i];
	}
	return sum0;
}

int knapsack_remainingbudget(const int prices[], const int nsize, const int budget, char cart[]) {
	return 0;
}
