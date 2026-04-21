#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から検討対象とする商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額,
//       cart はベストな購入で商品 i が選ばれているかどうかを格納する長さ nsize （以上の）列
int knapsack_recursive(const int prices[], const int budget, bool cart[]) {

	if ( prices[0] == 0 ) {
		// price 列の終端に至った
		return 0;
	}

	int sum_skipped, sum_bought;   	// prices[0] を購入しない場合と購入した場合それぞれの合計金額
	int nsize; 	// のこりの検討商品数
	for (nsize = 0; prices[nsize] ; ++nsize) { }
	bool bestcart[nsize];	// prices (prices[0] 以降) についてのよりよい購入リスト

	cart[0] = false;
	// C では配列とポインタと同じ, +1 は次の要素を先頭とする配列
	sum_skipped = knapsack_recursive(prices + 1, budget, cart + 1);

	if ( prices[0] <= budget ) {
		// prince[0] を購入できる，かつ prices[0] を購入する場合
		cart[0] = true;
		sum_bought = prices[0] + knapsack_recursive(prices + 1, budget - prices[0], cart1 + 1);
		if ( sum_bought > sum_skipped ) {
			// 購入すると合計額がより大きくなる場合, cart に cart1[0],...,cart1[nsize-1] をコピー
			for(int i = 0; i < nsize; ++i)
				cart[i] = cart1[i];
			return sum_bought;
		}
	}
	//購入しないと決定，cart[0],...,[nsize-1] に cart0[0],...,cart0[nsize-1] をコピー
	for(int i = 0; i < nsize; ++i) {
		cart[i] = cart0[i];
	}
	return sum_skipped;
}

int knapsack_remainingbudget(const int prices[], const int nsize, const int budget, char cart[]) {
	return 0;
}
