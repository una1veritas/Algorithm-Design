#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vector>

#define DEG2RAD(x)  ((M_PI / 180.0) * (x))

struct gpspt {
	double time, lat, lon;

public:
	gpspt(const double & t, const double & la, const double & lo) : time(t), lat(la), lon(lo) {}

	double distanceTo(const gpspt & q) {
		//http://dtan4.hatenablog.com/entry/2013/06/10/013724
		//https://en.wikipedia.org/wiki/Geographical_distance#Ellipsoidal_Earth_projected_to_a_plane
		//https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
		//const int mode = 1;
		// 緯度，経度をラジアンに
		double  plat = DEG2RAD(lat),
				plon = DEG2RAD(lon),
				qlat = DEG2RAD(q.lat),
				qlon = DEG2RAD(q.lon);
		// 緯度と経度の差
		//double latdiff = plat - qlat, londiff = plon - qlon;
		// 平均緯度
		double latavr = (plat + qlat) / 2.0;

		// 測地系による値の違い
		double a = 6378137.0; //mode ? 6378137.0 : 6377397.155; // 赤道半径
		double b = 6356752.314140356; //mode ? 6356752.314140356 : 6356078.963; // 極半径
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

};


int read_gpspt_csv(char * filename, std::vector<gpspt> & array) {
	char buff[1024];
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "file open failed.\n");
		return 0; // failed
	}
	double t, la, lo;
	while (fgets(buff, 1024, fp) != NULL) {
		sscanf(buff,"%lf,%lf,%lf",&t, &la, &lo);
		array.push_back(gpspt(t, la, lo));
	}
	fclose(fp);
	return 1; // succeeded
}

int main(int argc, char **argv) {
	if ( !(argc > 2) ) {
		fprintf(stderr, "two file names requested.\n");
		return EXIT_FAILURE;
	}
	std::vector<gpspt> parray, qarray;
	read_gpspt_csv(argv[1], parray);
	read_gpspt_csv(argv[2], qarray);

	printf("\n%s:\n", argv[1]);
	for(int i = 0; i < parray.size(); ++i) {
		printf("%d: %lf, %lf, %lf", i, parray[i].time, parray[i].lat, parray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", parray[i-1].distanceTo(parray[i]));
		printf("\n");
	}

	printf("%s:\n", argv[2]);
	for(int i = 0; i < qarray.size(); ++i) {
		printf("%d: %lf, %lf, %lf",
				i, qarray[i].time, qarray[i].lat, qarray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", qarray[i-1].distanceTo(qarray[i]));
		printf("\n");
	}

	return EXIT_SUCCESS; // return 0;
}
