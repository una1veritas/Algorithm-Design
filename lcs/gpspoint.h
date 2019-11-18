#ifndef _GPSPOINT_H_
#define _GPSPOINT_H_

#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <cmath>

/* Symbols for debug switches */
#define SHOW_TABLE
/* light-weight functions by MACRO */

#define DEG2RAD(x)  ((M_PI / 180.0) * (x))
#define ABS(x)  ((x) >= 0 ? (x) : -(x))
#define MAX_AMONG3(x, y, z)  ((x) > (y) ? ((x) > (z) ? (x) : (z)): ((y) > (z) ? (y) : (z)))
#define MIN(x, y)  ((y) < (x) ? (y) : (x))

struct gpspoint {
	double time, lat, lon;

private:
	constexpr static double epsilon = 1.0e-8;

	struct metvector {
		double x, y;

		metvector(const gpspoint & a, const gpspoint & b) {
			x = a.distanceTo(gpspoint(0, a.lat, b.lon));
			if (a.lon > b.lon) x = -x;
			y = a.distanceTo(gpspoint(0, b.lat, a.lon));
			if (a.lat > b.lat) y = -y;
		}
	};

	/*
	friend bool operator ==(const gpspoint &p, const gpspoint &q) {
		// emulate by ``take maximum'' norm.
		if ( abs(p.lat - q.lat) < gpspoint::epsilon
				&& abs(p.lon - q.lon) < gpspoint::epsilon )
			return true;
		return false;
	}

	friend gpspoint operator -(const gpspoint &p, const gpspoint &q) {
		return gpspoint(p.time - q.time, p.lat - q.lat, p.lon - q.lon);
	}

	gpspoint operator-(void) {
		return gpspoint(-this->time, -this->lat, -this->lon);
	}
	*/

	static double inner_prod(const gpspoint & a, const gpspoint & b, const gpspoint & c) {
		metvector ab(a,b), ac(a,c);
		//std::cout << "(" << ab.x << ", " << ab.y << ") * (" << ac.x << ", " << ac.y << ") " << std::endl;
		return (ab.x * ac.x) + (ab.y * ac.y);
	}

	static double norm_outer_prod(const gpspoint & a, const gpspoint & b,
			const gpspoint & c) {
		metvector ab(a, b), ac(a, c);
		return (ab.x * ac.y) - (ab.y * ac.x);
	}

public:
	gpspoint(const double &t, const double &la, const double &lo) :
			time(t), lat(la), lon(lo) {
	}

	double distanceTo(const gpspoint &q) const;
	double distanceToLine(const gpspoint &q1, const gpspoint &q2) const {
		if ( inner_prod(q1, q2, *this) < epsilon ) { // < 0.0
			return q1.distanceTo(*this);
		}
		if ( inner_prod(q2, q1, *this) < epsilon ) { // < 0.0
			return q2.distanceTo(*this);
		}
		return ABS(norm_outer_prod(q1, q2, *this)) / q1.distanceTo(q2);
	}

	typedef std::pair<unsigned int, unsigned int> uintpair;
	static std::pair<int, std::vector<uintpair>> lcs(std::vector<gpspoint> &pseq, std::vector<gpspoint> &qseq,const double &bound = 50.0);

	friend std::ostream & operator<<(std::ostream & os, const gpspoint & p) {
		os << "[" << std::fixed << std::setprecision(6) << p.time << ", " << p.lat << ", " << p.lon << "] ";
		return os;
	}
};

#endif /* _GPSPOINT_H_ */
