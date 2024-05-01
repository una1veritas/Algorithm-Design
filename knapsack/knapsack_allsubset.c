#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から購入を検討する商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額, cart はベストな購入で i 番目の商品が選ばれているかを格納
int knapsack_allsubset(const int prices[], int nsize, const int budget, char cart[]) {
	if ( nsize == 0 ) {
		cart[0] = 0;
		return 0;
	}

	int sum, best;
	int item;

	char subset[nsize+1]; 	// 計算中の仮の購入リストを宣言
	for(int i = 0; i < nsize+1; ++i)
		subset[i] = 0;  	// 仮の購入リストを空集合に初期化

	best = 0;
	for(; subset[nsize] == 0 ;) { 	// subset の nsize+1 ビット目は
									//終了フラグ（オーバーフロー）として使用する
		sum = 0;
		// 仮の購入リスト subset のアイテムの合計金額を求める
		for(item = 0; item < nsize && sum <= budget; ++item) {
			if (subset[item] != 0 )
				sum += prices[item];
		}
		// 合計が budget 以下かつ best より大きい場合 cart を更新する
		if (best < sum && sum <= budget ) {
			best = sum;
			// 仮の最もよい購入リストとして cart に subset を保存
			for(int i = 0; i < nsize; ++i)
				cart[i] = subset[i];
			cart[nsize] = 0;
		}
		// 部分集合 subset を二進数と見なしてインクリメントする
		for(item = 0; item < nsize + 1; ++item) {
			if ( subset[item] == 0 ) {
					subset[item] = 1;
					break;
			}
			subset[item] = 0;
		}
	}

	return best;
}
