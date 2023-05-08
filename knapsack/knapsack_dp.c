#include <stdio.h>
#include <stdlib.h>

// 入力： prices 商品の価格リスト, nsize リストの先頭から購入を検討する商品の数（リストの長さ）, budget 予算額
// 出力： 返値はベストな購入での合計額, cart はベストな購入で i 番目の商品が選ばれているかを格納
int knapsack_dp(const int prices[], int nsize, const int budget, char cart[]) {
	if ( nsize == 0 ) {
		cart[0] = 0;
		return 0;
	}

  int best[nsize][budget+1];
  
  // top row and left-most column
  int i = 0, b = 0;
  for (i = 0; i < nsize; i++) {
	  best[i][0] = 0 ;
  }
  for (b = 0; b <= budget; b++) {
	  best[0][b] = prices[0] <= b ? prices[0] : 0 ;
  }
  
  // fill up the DP-table by recurrence.
  int best_buy, best_skip;
  for (i = 1; i < nsize; i++) {
	  for (b = 1; b <= budget; b++) {
		  best_skip = best[i-1][b];
		  if (b >= prices[i]) {
			  best_buy = best[i-1][b - prices[i]] + prices[i];
			  best[i][b] = best_buy > best_skip ? best_buy : best_skip;
		  } else {
			  best[i][b] = best_skip;
		  }
	  }
  }

  // to show the dp-table.
  /*
  for(i = 0; i < nsize; ++i) {
	  for(b = 0; b <=budget; ++b) {
		  printf("%3d ", best[i][b]);
	  }
	  printf("\n");
  }
  printf("\n\n");
  */
  // back-track the table.
  // i must be a signed integer.
  for (i = nsize - 1, b = budget; i >= 0 ; i-- ) {
	  if ( best[i][b] == best[i-1][b]) {
		  // the i-th item was not bought
		  cart[i] = 0;
		  //printf("item %d skipped. b = %d\n", i, b);
	  } else if ( best[i][b] - prices[i] == best[i-1][b-prices[i]] ) {
		  // the i-th item was bought
		  cart[i] = 1;
		  b = b - prices[i];
		  //printf("prices[%d] = %d, b = %d\n", i, prices[i], b);
	  } else {
		  fprintf(stderr, "back tracking failed!\n");
	  }
  }

  /*
  cout << "(" << 0 << ", " << b << ") ";
  if (best[0][b] != 0)
    buylist.push_back(0);

  cout << endl << "Buy-list: ";
  for (vector<int>::iterator i = buylist.end(); i > buylist.begin(); ) {
    i--;
    cout << *i << ", ";
  }
  cout << "totally " << best[val.size()-1][budget] << " yen." << endl;
*/
  return best[nsize-1][budget];
}
