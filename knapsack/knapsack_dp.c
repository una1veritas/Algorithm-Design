#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から購入を検討する商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額, cart はベストな購入で i 番目の商品が選ばれているかを格納
int knapsack_dp(const int prices[], int nsize, const int budget, char cart[]) {
	if ( nsize == 0 ) {
		cart[0] = 0;
		return 0;
	}

  int best[nsize+1][budget+1];
  
  // top row and left-most column
  int i = 0, b = 0;
  for (b = 0; b <= budget; b++) {
	  best[0][b] = prices[0] <= b ? prices[0] : 0 ;
  }
  for (i = 0; i <= nsize; i++) {
	  best[i][0] = 0 ;
  }
  
  // fill up the DP-table by revurrence.
  int best_buy, best_skip;
  for (i = 1; i <= nsize; i++) {
	  for (b = 1; b <= budget; b++) {
		  best_skip = best[i-1][b];
		  if (b >= prices[i-1]) {
			  best_buy = best[i-1][b - prices[i-1]] + prices[i-1];
			  best[i][b] = best_buy > best_skip ? best_buy : best_skip;
		  } else {
			  best[i][b] = best_skip;
		  }
	  }
  }


  for (i = val.size() - 1, b = budget; i > 0 ; i-- ) {
    cout << "(" << i << ", " << b << ") ";
    if ( best[i][b] == best[i - 1][b] ) {
      //cout << "(skip " << i << "th) ";
    } else {
      //cout << i << " (" << val[i] << " yen), ";
      buylist.push_back(i);
      b = b - val[i];
    }
  }
  cout << "(" << 0 << ", " << b << ") ";
  if (best[0][b] != 0)
    buylist.push_back(0);

  cout << endl << "Buy-list: ";
  for (vector<int>::iterator i = buylist.end(); i > buylist.begin(); ) {
    i--;
    cout << *i << ", ";
  }
  cout << "totally " << best[val.size()-1][budget] << " yen." << endl;
  
  return 0;
}
