/*
 * geohash.h
 *
 *  Created on: 2022/03/21
 *      Author: Sin Shimozono
 *
 *   c++14 or later
 */

#ifndef GEOHASH_H_
#define GEOHASH_H_

#include <iostream>
#include <string>
#include <vector>

namespace geohash {
	static constexpr double MAX_LAT = 90.0;
	static constexpr double MIN_LAT = -90.0;
	static constexpr double MAX_LONG = 180.0;
	static constexpr double MIN_LONG = -180.0;
	static constexpr char * char_map = (char *) "0123456789bcdefghjkmnpqrstuvwxyz";
	static constexpr int bz_map[] = {
			10, 11, 12, 13, 14, 15, 16, -1,
			17, 18, -1,
			19, 20, -1,
			21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	};

	/*
	 *  The follow character maps were created by Dave Troy and used in his Javascript Geohashing
	 *  library. http://github.com/davetroy/geohash-js
	 */
	static constexpr char *even_neighbors[] = {
			(char *) "p0r21436x8zb9dcf5h7kjnmqesgutwvy",
			(char *) "bc01fg45238967deuvhjyznpkmstqrwx",
			(char *) "14365h7k9dcfesgujnmqp0r2twvyx8zb",
			(char *) "238967debc01fg45kmstqrwxuvhjyznp"
	};

	static constexpr char *odd_neighbors[] = {
			(char *) "bc01fg45238967deuvhjyznpkmstqrwx",
			(char *) "p0r21436x8zb9dcf5h7kjnmqesgutwvy",
			(char *) "238967debc01fg45kmstqrwxuvhjyznp",
			(char *) "14365h7k9dcfesgujnmqp0r2twvyx8zb"
	};

	static constexpr char *even_borders[] = {(char *) "prxz", (char *) "bcfguvyz", (char *) "028b", (char *) "0145hjnp"};
	static constexpr char *odd_borders[] = {(char *) "bcfguvyz", (char *) "prxz", (char *) "0145hjnp", (char *) "028b"};

	int char_revmap(const char c);
	int index(const char c, const std::string & str);

	struct interval {
		double high, low;

		interval(const double &hi, const double &lo) :
				high(hi), low(lo) {
		}
	};


	struct coordbox {
	    double n;
	    double e;
	    double s;
	    double w;

	    double center_lat() const {
	    	return n - (n-s)/2.0;
	    }

	    double center_lon() const {
	    	return e - (e-w)/2.0;
	    }

	    friend std::ostream & operator<<(std::ostream & out, const coordbox & box) {
	    	out << "(s: " << box.s << ", n: " << box.n
	    			<< ", w: " << box.w << ", e: " << box.e << ") ";
	    	return out;
	    }
	};

	uint64_t binvalue(const std::string & hash);
	std::string bincode(const std::string & hash);
	std::string encode(const double & lat, const double & lng, int length = 8);
	coordbox decode(const std::string & hash);

	enum {
		NORTH 		= 0,
		NORTHEAST 	= 1,
		EAST  		= 2,
		SOUTHEAST 	= 3,
		SOUTH 		= 4,
		SOUTHWEST 	= 5,
		WEST  		= 6,
		NORTHWEST 	= 7,
		DIRECTION_END = 8,
	};

	std::vector<std::string> neighbors(const std::string & hash, const int zone);

};

#endif /* GEOHASH_H_ */
