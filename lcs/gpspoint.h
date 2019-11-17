#ifndef _GPSPOINT_H_
#define _GPSPOINT_H_

#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <cmath>

/* Symbols for debug switches */
//#define SHOW_SEQ
//#define SHOW_TABLE
/* light-weight functions by MACRO */

#define DEG2RAD(x)  ((M_PI / 180.0) * (x))
#define MAX_AMONG3(x, y, z)  ((x) > (y) ? ((x) > (z) ? (x) : (z)): ((y) > (z) ? (y) : (z)))
#define ABS(x)  ((x) >= 0 ? (x) : -(x))

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

	double distanceToLine(const gpspoint &q1, const gpspoint &q2) const {
		if ( inner_prod(q1, q2, *this) < epsilon ) { // < 0.0
			return q1.distanceTo(*this);
		}
		if ( inner_prod(q2, q1, *this) < epsilon ) { // < 0.0
			return q2.distanceTo(*this);
		}
		return ABS(norm_outer_prod(q1, q2, *this)) / q1.distanceTo(q2);
	}

	double distanceTo(const gpspoint &q) const {
		//http://dtan4.hatenablog.com/entry/2013/06/10/013724
		//https://en.wikipedia.org/wiki/Geographical_distance#Ellipsoidal_Earth_projected_to_a_plane
		//https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
		//const int mode = 1;

		// convert degree values to radians
		double plat = DEG2RAD(lat), plon = DEG2RAD(lon), qlat = DEG2RAD(q.lat),
				qlon = DEG2RAD(q.lon);
		// 緯度と経度の差
		//double latdiff = plat - qlat, londiff = plon - qlon;
		// the average of lattitude values
		double latavr = (plat + qlat) / 2.0;

		// 測地系による値の違い
		double a = 6378137.0; //mode ? 6378137.0 : 6377397.155; // 赤道半径
		//double b = 6356752.314140356; //mode ? 6356752.314140356 : 6356078.963; // 極半径
		//$e2 = ($a*$a - $b*$b) / ($a*$a);
		double e2 = 0.00669438002301188; //mode ? 0.00669438002301188 : 0.00667436061028297; // 第一離心率^2
		//$a1e2 = $a * (1 - $e2);
		double a1e2 = 6335439.32708317; // mode ? 6335439.32708317 : 6334832.10663254; // 赤道上の子午線曲率半径

		double sin_latavr = sin(latavr);
		double W2 = 1.0 - e2 * (sin_latavr * sin_latavr);
		double M = a1e2 / (sqrt(W2) * W2); // 子午線曲率半径M
		double N = a / sqrt(W2); // 卯酉線曲率半径

		double t1 = M * (plat - qlat); //latdiff;
		double t2 = N * cos(latavr) * (plon - qlon); //londiff;
		return sqrt((t1 * t1) + (t2 * t2));
	}

	typedef std::pair<unsigned int, unsigned int> uintpair;

	static std::pair<int, std::vector<gpspoint::uintpair>> lcs(
			std::vector<gpspoint> &pseq, std::vector<gpspoint> &qseq,
			const double &bound = 50.0) {
		unsigned short int dtable[pseq.size()][qseq.size()];
		unsigned int ip, iq;
		// computing the left- and top- frame cells as base-steps
		for (ip = 0; ip < pseq.size(); ++ip) {
#ifdef SHOW_TABLE
			printf("(%lf, %lf) - (%lf, %lf): %lf, \n",
					pseq[ip].lat, pseq[ip].lon, qseq[0].lat, qseq[0].lon,
					pseq[ip].distanceTo(qseq[0]));
#endif
			if (pseq[ip].distanceTo(qseq[0]) <= bound) {
				dtable[ip][0] = 1;
			} else {
				dtable[ip][0] = 0;
			}
		}
		for (iq = 0; iq < qseq.size(); ++iq) {
			if (pseq[0].distanceTo(qseq[iq]) <= bound) {
				dtable[0][iq] = 1;
			} else {
				dtable[0][iq] = 0;
			}
		}
		// computing inner cells by the inductive relation
		for (iq = 1; iq < qseq.size(); ++iq) {
			for (ip = 1; ip < pseq.size(); ++ip) {
				if (pseq[ip].distanceTo(qseq[iq]) <= bound) {
					dtable[ip][iq] = dtable[ip - 1][iq - 1] + 1;
				} else {
					dtable[ip][iq] = MAX_AMONG3(dtable[ip - 1][iq - 1],
							dtable[ip][iq - 1], dtable[ip - 1][iq]);
				}
			}
		}
#ifdef SHOW_TABLE
		for(iq = 320; iq < qseq.size(); ++iq) {
			printf("%u:\t", iq);
			for(ip = 210; ip < pseq.size(); ++ip) {
				printf("%u, ", dtable[ip][iq]);
			}
			printf("\n");
		}
#endif
		// back track the subsequence
		std::vector<uintpair> matchedpairs;
		ip = pseq.size() - 1;
		iq = qseq.size() - 1;
		while (ip > 0 && iq > 0) {
			if (dtable[ip][iq] == dtable[ip - 1][iq - 1]) {
				ip -= 1;
				iq -= 1;
				// printf("\\");
				continue;
			}
			if (dtable[ip][iq] == dtable[ip][iq - 1]) {
				iq -= 1;
				// printf("^");
				continue;
			}
			if (dtable[ip][iq] == dtable[ip - 1][iq]) {
				ip -= 1;
				// printf("<");
				continue;
			}
			if (dtable[ip][iq] == dtable[ip - 1][iq - 1] + 1) {
				matchedpairs.push_back(uintpair(ip, iq));
				// printf("(%d, %d)", ip, iq);
				ip -= 1;
				iq -= 1;
				continue;
			}
			printf("error!\n");
			break;
			//printf("(%d, %d), ", ip, iq);
		}
		//printf("\n");
		std::reverse(matchedpairs.begin(), matchedpairs.end());
		return std::pair<int, std::vector<uintpair> >(
				dtable[pseq.size() - 1][qseq.size() - 1], matchedpairs);
	}

	friend std::ostream & operator<<(std::ostream & os, const gpspoint & p) {
		os << "[" << std::fixed << std::setprecision(6) << p.time << ", " << p.lat << ", " << p.lon << "] ";
		return os;
	}
};

#endif /* _GPSPOINT_H_ */
