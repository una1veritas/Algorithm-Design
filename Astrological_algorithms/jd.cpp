//============================================================================
// Name        : JulianDayNumber.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

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
	//test
	int year = 2011;
	int month = 10;
	double date = 12;
	double jd = 2436116.31;

	// process input
	if ( argc == 2 ) {
		jd = atof(argv[1]);
	} else if ( argc == 4 ) {
		year = atoi(argv[1]);
		month = atoi(argv[2]);
		date = atof(argv[3]);
	}
	cout << "Input: ";
	cout << "Year " << year << ", month " << month << ", date " << date << endl;
	//
	cout << "INT(-4.98) = " << INT(-4.98) << endl;
	//
	jd = JulianDay(year, month, date);
	cout << "Julian Day number = "<< INT(jd) << "." << INT(jd*10)%10 << INT(jd*100)%10 << endl << endl;
	cout << "Day of the week = " << INT(INT(jd)+1.5) %7 << "." << endl;
	double cal = CalendarDate((double)1507900.13);
	cout << "Calendar date is "<< setprecision(10) << cal << endl;

	return 0;
}

double CalendarDate(double jd) {
	jd += 0.5;
	long z = INT(jd);
	long a = z;
	double f = FRAC(jd);
	if ( z >= 2299161 ) {
		long alpha = INT( (z-1867216.25)/36524.25 );
		a += 1 + alpha - INT(alpha/4);
	}
	long b = a + 1524;
	long c = INT( (b-122.1)/365.25 );
	long d = INT(365.25 * c);
	long e = INT( (b-d)/30.6001 );
	double day = b - d - INT(30.6001 * e) + f;
	int month;
	if ( e < 13.5 ) {
		month = e - 1;
	} else {
		month = e-13;
	}
	long year;
	if ( month > 2.5) {
		year = c - 4716;
	} else {
		year = c - 4715;
	}
	return SIGN(year)*(abs(year)*10000 + month*100 + day);
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

