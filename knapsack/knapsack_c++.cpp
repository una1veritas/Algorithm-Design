//============================================================================
// Name        : Knapsack.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#include <ctime>

using namespace std;


#define MAX(X, Y) ((X) < (Y) ? (Y) : (X))

int list4[] = { 108, 78, 78, 64, 0 };
int list8[] = { 108, 78, 78, 68, 58, 48, 128, 98, 0 };
int list10[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 0 };
int list20[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78,
		78, 58, 158, 68, 128, 98, 0 };
int list25[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78,
		78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 0 };
int list30[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78,
		78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64,
		178, 0 };
int list32[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78,
		78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64,
		178, 115, 138, 0 };
int list34[] = { 108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78,
		78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64,
		178, 115, 138, 148, 88, 0 };

int * plist = list25;
const int B = 400;

int best(int lastitem, int budget, bool cart[]) {
	// lastitem == 0
	if (lastitem == 0) {
		if (plist[lastitem] <= budget) {
			cart[0] = true;
			return plist[lastitem];
		} else { /* if ( plist[lastitem] > budget) */
			cart[0] = false;
			return 0;
		}
	}
	// lastitem >= 1
	bool cart_bought[lastitem], cart_not_bought[lastitem];
	int bought = plist[lastitem]
			+ best(lastitem - 1, budget - plist[lastitem], cart_bought);
	int not_bought = best(lastitem - 1, budget, cart_not_bought);
	if (bought <= budget and bought > not_bought) {
		for (int i = 0; i < lastitem; i++)
			cart[i] = cart_bought[i];
		cart[lastitem] = true;
		return bought;
	} else {
		for (int i = 0; i < lastitem; i++)
			cart[i] = cart_not_bought[i];
		cart[lastitem] = false;
		return not_bought;
	}
}

int best_dp(const int lastitem, const int budget, bool cart[]) {
	int best[lastitem + 1][budget + 1];
	int bought, not_bought;
	for (int b = 0; b <= budget; b++) {
		for (int item = 0; item <= lastitem; item++) {
			if (item == 0) {
				if (plist[0] <= b) {
					best[0][b] = plist[0];
				} else /* if (plist[item] > b) */{
					best[0][b] = 0;
				}
			} else /* if (item >= 0) */{
				bought = plist[item] + best[item - 1][MAX(b - plist[item], 0 )]; //, cart_bought);
				not_bought = best[item - 1][b]; //, cart_not_bought);
				if (bought <= b and bought > not_bought) {
					best[item][b] = bought;
				} else {
					best[item][b] = not_bought;
				}
			}
		}
	}
	// back-track
	int b = budget;
	for(int item = lastitem; item >= 0; item--) {
		if ( best[item][b] - plist[item] == best[item-1][b-plist[item]] ) {
			cart[item] = true;
			b = b - plist[item];
		} else {
			cart[item] = false;
			// not bought
		}
	}
	/*
	for(int b = 0; b <= budget; ++b) {
		cout << setw(3) << b << ": ";
		for(int i = 0; i < lastitem+1; ++i) {
			cout << setw(4) << best[i][b] << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/
	return best[lastitem][budget];
}

/*
Budget: 300,
34 Items:
108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64, 178, 115, 138, 148, 88,
Elapsed in function "best": 364.614 sec.
Elapsed in function "best_dp": 0.000139 sec.

(0)108, (1)78, (2)78, (3)58, (4)58, (5)68, (6)38, (7)39, (8)58, (9)128, (10)158, (11)108, (12)138, (13)78, (14)78, (15)58, (16)158, (17)68, (18)128, (19)98, (20)158, (21)118, (22)128, (23)328, (24)228, (25)238, (26)198, (27)298, (28)64, (29)178, (30)115, (31)138, (32)148, (33)88,
Recommended total price is 300 with these items 28 32 33 .
 */

int main(int argc, char ** argv) {
	int itemnum;

	cout << "Budget: " << B << "," << endl;
	for (itemnum = 0; plist[itemnum] > 0; itemnum++)
		;

	cout << itemnum << " Items: " << endl;
	for (itemnum = 0; plist[itemnum] > 0; itemnum++) {
		cout << plist[itemnum] << ", ";
	}
	cout << endl;

	bool shoppingCart[itemnum];

	clock_t swatch;
	int result;
	swatch = clock();
	result = best(itemnum - 1, B, shoppingCart);
	swatch = clock() - swatch;
	cout << "Elapsed time in function \"best\": " << double(swatch) / 1000000L
			<< " sec. " << endl;

	cout << " Cart: ";
	for (itemnum = 0; plist[itemnum] > 0; itemnum++) {
		if ( shoppingCart[itemnum] )
			cout << itemnum << " (" << plist[itemnum] << "), ";
	}
	cout << endl << endl;


	swatch = clock();
	result = best_dp(itemnum - 1, B, shoppingCart);
	swatch = clock() - swatch;
	cout << "Elapsed time in function \"best_dp\": " << double(swatch) / 1000000L
			<< " sec. " << endl;

	cout << "Recommended total price is " << result << " with these items ";
	for (itemnum = 0; plist[itemnum] > 0; itemnum++) {
		if (shoppingCart[itemnum]) {
			cout << itemnum << " (" << plist[itemnum] << "), ";
		}
	}
	cout << "." << endl;

	return 0; // finished without errors.
}

/*
Budget: 400,
25 Items:
108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228,
Elapsed time in function "best": 0.233844 sec.
 Cart: 1 (78), 2 (78), 3 (58), 4 (58), 9 (128),

Elapsed time in function "best_dp": 4.7e-05 sec.
Recommended total price is 400 with these items 6 (38), 8 (58), 15 (58), 21 (118), 22 (128), .

Budget: 400,
30 Items:
108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64, 178,
Elapsed time in function "best": 6.49217 sec.
 Cart: 1 (78), 2 (78), 3 (58), 4 (58), 9 (128),

Elapsed time in function "best_dp": 5.6e-05 sec.
Recommended total price is 400 with these items 20 (158), 28 (64), 29 (178), .


Budget: 400,
32 Items:
108, 78, 78, 58, 58, 68, 38, 39, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64, 178, 115, 138,
Elapsed time in function "best": 28.6292 sec.
 Cart: 1 (78), 2 (78), 3 (58), 4 (58), 9 (128),

Elapsed time in function "best_dp": 6e-05 sec.
Recommended total price is 400 with these items 7 (39), 11 (108), 30 (115), 31 (138), .

 */
