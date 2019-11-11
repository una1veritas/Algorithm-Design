#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vector>
#include <algorithm>

/* Symbols for debug switches */
//#define SHOW_SEQ
//#define SHOW_TABLE

/* light-weight functions by MACRO */
#define DEG2RAD(x)  ((M_PI / 180.0) * (x))
#define MAX_AMONG3(x, y, z)  ((x) > (y) ? ((x) > (z) ? (x) : (z)): ((y) > (z) ? (y) : (z)))

struct gpspoint {
	double time, lat, lon;

public:
	gpspoint(const double & t, const double & la, const double & lo) : time(t), lat(la), lon(lo) {}

	double distanceTo(const gpspoint & q) {
		//http://dtan4.hatenablog.com/entry/2013/06/10/013724
		//https://en.wikipedia.org/wiki/Geographical_distance#Ellipsoidal_Earth_projected_to_a_plane
		//https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
		//const int mode = 1;

		// convert degree values to radians
		double  plat = DEG2RAD(lat),
				plon = DEG2RAD(lon),
				qlat = DEG2RAD(q.lat),
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
		double W2 = 1.0 - e2 * (sin_latavr*sin_latavr);
		double M = a1e2 / (sqrt(W2)*W2); // 子午線曲率半径M
		double N = a / sqrt(W2); // 卯酉線曲率半径

		double t1 = M * (plat - qlat); //latdiff;
		double t2 = N * cos(latavr) * (plon - qlon); //londiff;
		return sqrt((t1*t1) + (t2*t2));
	}

	typedef std::pair<unsigned int, unsigned int>  uintpair;
	static std::pair<int, std::vector<uintpair> > lcs(std::vector<gpspoint> & pseq, std::vector<gpspoint> & qseq, const double & epsilon = 50.0) {
		unsigned short int cslength[pseq.size()][qseq.size()];
		unsigned int ip, iq;
		// computing the left- and top- frame cells as base-steps
		for(unsigned ip = 0; ip < pseq.size(); ++ip) {
#ifdef SHOW_TABLE
			printf("(%lf, %lf) - (%lf, %lf): %lf, \n",
					pseq[ip].lat, pseq[ip].lon, qseq[0].lat, qseq[0].lon,
					pseq[ip].distanceTo(qseq[0]));
#endif
			if ( pseq[ip].distanceTo(qseq[0]) <= epsilon ) {
				cslength[ip][0] = 1;
			} else {
				cslength[ip][0] = 0;
			}
		}
		for(iq = 0; iq < qseq.size(); ++iq) {
			if ( pseq[0].distanceTo(qseq[iq]) <= epsilon ) {
				cslength[0][iq] = 1;
			} else {
				cslength[0][iq] = 0;
			}
		}
		// computing inner cells by the inductive relation
		for(iq = 1; iq < qseq.size(); ++iq) {
			for(ip = 1; ip < pseq.size(); ++ip) {
				if ( pseq[ip].distanceTo(qseq[iq]) <= epsilon ) {
					cslength[ip][iq] = cslength[ip - 1][iq - 1] + 1;
				} else {
					cslength[ip][iq] = MAX_AMONG3(cslength[ip - 1][iq - 1],
							cslength[ip][iq - 1], cslength[ip - 1][iq]);
				}
			}
		}
#ifdef SHOW_TABLE
		for(iq = 0; iq < qseq.size(); ++iq) {
			printf("%u:\t", iq);
			for(ip = 0; ip < pseq.size(); ++ip) {
				printf("%u, ", cslength[ip][iq]);
			}
			printf("\n");
		}
#endif
		// back track the subsequence
		std::vector<uintpair> matchedpairs;
		ip = pseq.size() - 1;
		iq = qseq.size() - 1;
		while ( ip > 0 && iq > 0 ) {
			if ( cslength[ip][iq] == cslength[ip - 1][iq - 1] ) {
				ip -= 1;
				iq -= 1;
				continue;
			}
			if ( cslength[ip][iq] == cslength[ip][iq - 1] ) {
				iq -= 1;
				continue;
			}
			if ( cslength[ip][iq] == cslength[ip - 1][iq] ) {
				ip -= 1;
				continue;
			}
			if ( cslength[ip][iq] == cslength[ip - 1][iq - 1] + 1 ) {
				ip -= 1;
				iq -= 1;
				matchedpairs.push_back(uintpair(ip, iq));
				continue;
			}
			printf("error!\n");
			break;
			//printf("(%d, %d), ", ip, iq);
		}
		//printf("\n");
		//std::reverse(matchedpairs.begin(), matchedpairs.end());
		return std::pair<int, std::vector<uintpair> >(cslength[pseq.size() - 1][qseq.size() - 1], matchedpairs);
	}
};


int read_gpspt_csv(char * filename, std::vector<gpspoint> & array) {
	char buff[1024];
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "file open failed.\n");
		return 0; // failed
	}
	double t, la, lo;
	while (fgets(buff, 1024, fp) != NULL) {
		sscanf(buff,"%lf,%lf,%lf",&t, &la, &lo);
		array.push_back(gpspoint(t, la, lo));
	}
	fclose(fp);
	return 1; // succeeded
}

int main(int argc, char **argv) {
	if ( !(argc > 2) ) {
		fprintf(stderr, "two file names requested.\n");
		return EXIT_FAILURE;
	}
	std::vector<gpspoint> parray, qarray;
	read_gpspt_csv(argv[1], parray);
	read_gpspt_csv(argv[2], qarray);

	printf("\n%s:\n", argv[1]);
#ifdef SHOW_SEQ
	for(int i = 0; i < parray.size(); ++i) {
		printf("%d: %lf, %lf, %lf", i, parray[i].time, parray[i].lat, parray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", parray[i-1].distanceTo(parray[i]));
		printf("\n");
	}
#endif
	printf("%s:\n", argv[2]);
#ifdef SHOW_SEQ
	for(int i = 0; i < qarray.size(); ++i) {
		printf("%d: %lf, %lf, %lf",
				i, qarray[i].time, qarray[i].lat, qarray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", qarray[i-1].distanceTo(qarray[i]));
		printf("\n");
	}
#endif
	std::pair<int, std::vector<gpspoint::uintpair>> result = gpspoint::lcs(parray, qarray);
	printf("the length of a longest common subsequence is %d.\n", result.first);
	for(auto i = result.second.begin(); i != result.second.end(); ++i) {
		gpspoint p = parray[i->first], q = qarray[i->second];
		printf("(%d [%lf, %lf], %d [%lf, %lf]) %lf, \n", i->first, p.lat, p.lon, i->second, q.lat, q.lon, p.distanceTo(q));
	}
	printf("\n");
	return EXIT_SUCCESS; // return 0;
}
