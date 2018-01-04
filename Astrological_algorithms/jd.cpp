//============================================================================
// Name        : JulianDayNumber.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#include <cstdlib>

using namespace std;

double JulianDay(int, int, double);
double CalendarDate(double);
unsigned int DayofWeek(double);

// integer part of (possibly) FP value w/ the same sign
#define INT(x) 	((long int) (x))
// fractional part of (possibly) FP value w/ the same sign
#define FRAC(x) ((x) - ((long int) (x)))
// -1 for values less than 0, 0 for 0, and 1 for others
#define SIGN(x) ((x) < 0 ? -1 : ( (x) > 0 ? 1 : 0))

int main(int argc, char * argv[]) {
	//set dummy values
	int year = 1966, month = 4;
	double date = 7, jd = 2458123.20;

	// process input
	if ( argc == 2 ) {
		jd = atof(argv[1]);
	} else if ( argc == 4 ) {
		year = atoi(argv[1]);
		month = atoi(argv[2]);
		date = atof(argv[3]);
	} else {
		std::cerr << "input error." << std::endl;
		return EXIT_FAILURE;
	}
	//
	cout << "Input: ";
	cout << "Year " << year << ", month " << month << ", date " << date << endl;
	//
	jd = JulianDay(year, month, date);
	cout << "Julian Day number = "<< INT(jd) << "." << INT(jd*10)%10 << INT(jd*100)%10 << endl;
	cout << "Day of the week = " << INT(INT(jd)+1.5) %7 << "." << endl;
	cout << endl;
	double cal = CalendarDate(jd);
	cout << "Calendar date is "<< setprecision(10) << cal << endl;

	return 0;
}

double CalendarDate(double jd) {
	/*
	 * 400 REM CALENDAR DATE FROM THE JD
410 CLS: INPUT"JD=";JD
420 IF JD<0 THEN PRINT "NEG JD ERROR":GOTO 400
425 JD=JD+0.5
430 Z=FIX(JD)
440 F=FRAC(JD)
450 IF Z<2299161 THEN A=Z
460 IF Z>=2299161 THEN ALPHA=FIX((Z-1867216.25)/36524.25):A=Z+1+ALPHA-FIX(ALPHA/4)
470 B=A+1524
480 C=FIX((B-122.1)/365.25)
490 D=FIX(365.25*C)
500 E=FIX((B-D)/30.6001)
510 DOM=B-D-FIX(30.6001*E)+F
520 IF E<13.5 THEN MON=E-1
530 IF E>13.5 THEN MON=E-13
540 IF MON>2.5THEN YER=C-4716
550 IF MON<2.5THEN YER=C-4715
560 PRINT YER;"/";MON;"/";DOM
570 RETURN
	 */
	jd += 0.5;
	long z = INT(jd);
	double f = FRAC(jd);
	long a;
	if ( z <  2299161 ) {
		a = z;
	} else {
		long alpha = INT( (z-1867216.25)/36524.25 );
		a = z + 1 + alpha - INT(alpha/4);
	}
	long b = a + 1524;
	long c = INT( (b-122.1)/365.25 );
	long d = INT(365.25 * c);
	long e = INT( (b-d)/30.6001 );
	double date = b - d - INT(30.6001 * e) + f;
	int month;
	if ( e < 13.5 ) {
		month = e - 1;
	} else { // if ( e > 13.5 ) {
		month = e-13;
	}
	long year;
	if ( month > 2.5) {
		year = c - 4716;
	} else {
		year = c - 4715;
	}
	return SIGN(year)*(abs(year)*10000 + month*100 + date);
}

double JulianDay(int y, int m, double d) {
	if ( m <= 2 ) {
		m = m + 12;
		y = y - 1;
	}
	int a = 0, b = 0;
	if ( y*10000+m*100+d >= 15821015 ) {
		a = INT(y/100);
		b = 2 - a + INT(a/4);
	}
	return INT(365.25 * y) + INT(30.6001 * (m+1)) + d + b + 1720994.5;
}

unsigned int DayofWeek(double jd) {
	return INT(jd+1.5) %7;
}

