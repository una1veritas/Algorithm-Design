/*
 * geohash.cpp
 *
 *  Created on: 2022/03/21
 *      Author: Sin Shimozono
 *
 *   c++14 or later
 */

//#include <iostream>
//#include <string>
//#include <vector>
#include <cinttypes>

# include "geohash.h"

using namespace std;

int geohash::char_revmap(const char c) {
	int result = -1;
	if (c < '9' + 1) {
		//"0123456789"
		result = c - '0';
	} else if (c < 'z' + 1) {
		result = bz_map[c - 'b'];
	}
	if (result < 0)
		return -1;
	return result;
}

int geohash::index(const char c, const string &str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		if (c == str[i])
			return i;
	}
	return -1;
}

struct interval {
	double high, low;

	interval(const double &hi, const double &lo) :
			high(hi), low(lo) {
	}
};

uint64_t geohash::binvalue(const string &hash) {
	uint64_t value = 0;
	if (hash.length() == 0)
		return value;
	for (unsigned int pos = 0; pos < hash.length(); ++pos) {
		int cval = char_revmap(hash[pos]);
		if (cval < 0)
			break;
		for (unsigned int i = 0; i < 5; ++i) {
			value <<= 1;
			value |= (cval & 0x10) ? 1 : 0;
			cval <<= 1;
		}
	}
	value <<= (64 - hash.length() * 5);
	return value;
}

string geohash::bincode(const string &hash) {
	string binary;
	for (unsigned int pos = 0; pos < hash.length(); ++pos) {
		int cval = char_revmap(hash[pos]);
		if (cval < 0)
			break;
		for (unsigned int i = 0; i < 5; ++i) {
			binary += (cval & 0x10) ? "1" : "0";
			cval <<= 1;
		}
	}
	return binary;
}

string geohash::encode(const double &lat, const double &lng, int length) {
	static char hash[12];
	if (length < 1)
		length = 1;
	else if (length > 12)
		length = 12;
	if (lat <= 90.0 && lat >= -90.0 && lng <= 180.0 && lng >= -180.0) {
		hash[length] = '\0';

		length *= 5.0;

		interval lat_interval(MAX_LAT, MIN_LAT);
		interval lng_interval(MAX_LONG, MIN_LONG);

		interval *intv;
		double coord, mid;
		int is_even = 1;
		unsigned int hashChar = 0;
		int i;
		for (i = 1; i <= length; i++) {
			if (is_even) {
				intv = &lng_interval;
				coord = lng;
			} else {
				intv = &lat_interval;
				coord = lat;
			}
			mid = (intv->low + intv->high) / 2.0;
			hashChar = hashChar << 1;
			if (coord > mid) {
				intv->low = mid;
				hashChar |= 0x01;
			} else
				intv->high = mid;

			if (!(i % 5)) {
				hash[(i - 1) / 5] = char_map[hashChar];
				hashChar = 0;
			}
			is_even = !is_even;
		}
	} else {
		hash[0] = '\0';
	}
	return string(hash);
}

geohash::coordbox geohash::decode(const string &hash) {
	coordbox box = { 0.0, 0.0, 0.0, 0.0 };

	if (hash.length() > 0) {
		unsigned int char_mapIndex;
		interval lat_interval = { MAX_LAT, MIN_LAT };
		interval lng_interval = { MAX_LONG, MIN_LONG };
		interval *intv;

		int is_even = 1;
		double delta;
		unsigned int i, j;
		for (i = 0; i < hash.length(); i++) {
			char_mapIndex = geohash::char_revmap(hash[i]);
			if (char_mapIndex < 0)
				break;
			// Interpret the last 5 bits of the integer
			for (j = 0; j < 5; j++) {
				intv = is_even ? &lng_interval : &lat_interval;
				delta = (intv->high - intv->low) / 2.0;
				if ((char_mapIndex << j) & 0x0010)
					intv->low += delta;
				else
					intv->high -= delta;

				is_even = !is_even;
			}
		}
		box.n = lat_interval.high;
		box.e = lng_interval.high;
		box.s = lat_interval.low;
		box.w = lng_interval.low;
	}
	return box;
}

vector<string> geohash::neighbors(const string &hash, const int zone) {
	vector<string> codes;
	if (zone < 1) {
		codes.push_back(hash);
		return codes;
	}
	coordbox box = decode(hash);
	int prec = hash.length();
	double width = box.e - box.w;
	double height = box.n - box.s;
	double lat = box.n - height / 2.0;
	double lon = box.e - width / 2.0;
	//cout << "center: " << lat << ", " << lon << "; ";
	int side = 2 * zone + 1;
	int inner = 2 * (zone - 1) + 1;
	// starts from upper left
	double gplat = lat + zone * height, gplon = lon - zone * width;
	int mvdir;
	for (int i = inner * inner; i < side * side; ++i) {
		codes.push_back(encode(gplat, gplon, prec));
		mvdir = ((i - inner * inner) / (side - 1)) % 4;
		//cout << i << " " << mvdir << ": " << gplat << ", " << gplon << "; ";
		switch (mvdir) {
		case 0: // r
			gplon += width;
			break;
		case 1: // d
			gplat -= height;
			break;
		case 2: // l
			gplon -= width;
			break;
		case 3: // u
			gplat += height;
		}
		if (gplon >= 180.0) {
			gplon = -(gplon - 360.0);
		}
		if (gplon < -180.0) {
			gplon += 360.0;
		}
	}
	//cout << endl;
	return codes;
}

