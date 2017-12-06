#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define INT(x) ((long)(x))
#define FRAC(x) ((x) - ((long)(x)))

int main(int argc, char * argv[]) {
  long yy, mm;
  double dd;

  double jd;
  int wday;

  cout << ((int) -4.2 ) << std::endl;

  if ( argc != 2 ) {
	  return EXIT_FAILURE;
  }

  double date = strtod(argv[1], NULL);
  cout << "date = " << date << std::endl;

  yy = date / 10000;
  date = ABS(date);
  mm = (INT(date) /100) % 100;
  dd = (INT(date)) % 100 + FRAC(date);

  cout << "YY = " << yy << " MM = " << mm << " DD = " << dd << std::endl;
  if ( mm <= 2 ) {
    yy -= 1;
    mm += 12;
  }

  int a, b = 0;
  if ( yy*10000+mm*100+dd >= 15821015 ) {
	  a = (int)(yy/100);
	  b = 2 - a + (int)(a/4);
  }
  jd = int(365.25 * yy) + int(30.6001 * (mm+1)) + dd + 1720994.5 + b;
  wday = int(jd + 1.5) % 7;

  cout << "jd = " << setprecision (2) << fixed << jd << endl;
  cout << "Day of Week = " << wday << endl;

  return 0;
}
