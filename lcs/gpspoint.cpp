/*
 * gpspoint.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: sin
 */

#include "gpspoint.h"

double gpspoint::distanceTo(const gpspoint &q) const {
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

double gpspoint::distanceTo(const gpspoint &q1, const gpspoint &q2) const {
	if ( inner_prod(q1, q2, *this) < epsilon ) { // < 0.0
		return q1.distanceTo(*this);
	}
	if ( inner_prod(q2, q1, *this) < epsilon ) { // < 0.0
		return q2.distanceTo(*this);
	}
	return ABS(norm_outer_prod(q1, q2, *this)) / q1.distanceTo(q2);
}


std::pair<int, std::vector<gpspoint::uintpair>> gpspoint::lcs(
		std::vector<gpspoint> &pseq, std::vector<gpspoint> &qseq,
		const double &bound) {
	unsigned short int dtable[(pseq.size() << 1) - 1][(qseq.size() << 1) - 1];
	unsigned int ip, iq;
	// computing the left- and top- frame cells as base-steps
	for (ip = 0; ip < (pseq.size()<<1)-1; ++ip) {
		dtable[ip][0] = 0;
		if ( (ip & 1) == 0 ) {
			if ( pseq[ip>>1].distanceTo(qseq[0]) <= bound )
				dtable[ip][0] = 2;
		} else if ( qseq[0].distanceTo(pseq[ip>>1], pseq[(ip>>1)+1]) <= bound ) {
			dtable[ip][0] = 1;
		}
	}
#ifdef SHOW_TABLE
	printf("   :\t");
	for(ip = 0; ip < (pseq.size()<<1)-1 ; ++ip) {
		printf("%3u, ", ip);
	}
	printf("\n");
	printf("%3u:\t", 0);
	for(ip = 0; ip < (pseq.size()<<1)-1 ; ++ip) {
		printf("%3u, ", dtable[ip][0]);
	}
	printf("\n\n");
#endif
	for (iq = 0; iq < (qseq.size()<<1)-1; ++iq) {
		dtable[0][iq] = 0;
		if ( (iq & 1) == 0 ) {
			if (qseq[iq>>1].distanceTo(pseq[0]) <= bound)
				dtable[0][iq] = 2;
		} else {
			if ( pseq[0].distanceTo(pseq[ip>>1], pseq[(ip>>1)+1]) <= bound )
				dtable[0][iq] = 1;
		}
	}
	// computing inner cells by the inductive relation
	for (iq = 1; iq < (qseq.size()<<1)-1; ++iq) {
		for (ip = 1; ip < (pseq.size()<<1)-1; ++ip) {
			if ( (iq & 1) == 0 && (ip & 1) == 0 ) {
				if (pseq[ip>>1].distanceTo(qseq[iq>>1]) <= bound) {
					dtable[ip][iq] = dtable[ip - 2][iq - 2] + 2;
				} else {
					dtable[ip][iq] = MAX_AMONG3(
							dtable[ip - 2][iq - 2],
							dtable[ip][iq - 2],
							dtable[ip - 2][iq]);
				}
			} else {
				dtable[ip][iq] = 0;
				/*
				dtable[ip][iq] = MAX_AMONG3(
						dtable[ip-1][iq-1],
						dtable[ip][iq-1],
						dtable[ip-1][iq]);
						*/
			}
		}
	}
#ifdef SHOW_TABLE
	const unsigned int ip_start = 0;//72;
	const unsigned int ip_stop = MIN(400, (pseq.size()<<1)-1);
	printf("   :\t");
	for(ip = ip_start; ip < ip_stop ; ++ip) {
		printf("%3u, ", ip);
	}
	printf("\n");
	for(iq = 0; iq < (qseq.size()<<1)-1; ++iq) {
		printf("%3u:\t", iq);
		for(ip = ip_start; ip < ip_stop ; ++ip) {
			printf("%3u, ", dtable[ip][iq]);
		}
		printf("\n");
	}
#endif
	// back track the subsequence
	std::vector<uintpair> matchedpairs;
	ip = (pseq.size()<<1) - 2;
	iq = (qseq.size()<<1) - 2;
	while (ip > 0 && iq > 0) {
		//printf("(%d, %d), ", ip, iq);
		if (dtable[ip][iq] == dtable[ip - 2][iq - 2]) {
			ip -= 2;
			iq -= 2;
			// printf("\\");
		} else if (dtable[ip][iq] == dtable[ip][iq - 2]) {
			iq -= 2;
			// printf("^");
		} else if (dtable[ip][iq] == dtable[ip - 2][iq]) {
			ip -= 2;
			// printf("<");
		} else if (dtable[ip][iq] == dtable[ip - 2][iq - 2] + 2) {
			matchedpairs.push_back(uintpair(ip, iq));
			printf("(%d, %d)", ip, iq);
			ip -= 2;
			iq -= 2;
		} else {
			printf("error!\n");
			break;
		}
	}
	//printf("\n");
	std::reverse(matchedpairs.begin(), matchedpairs.end());
	return std::pair<int, std::vector<uintpair>>(
			dtable[(pseq.size()<<1) - 2][(qseq.size()<<1) - 2], matchedpairs);
}