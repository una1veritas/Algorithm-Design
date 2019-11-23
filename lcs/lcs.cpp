#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vector>
#include "gpspoint.h"

//#define SHOW_SEQ

int read_gpspoint_csv(char *filename, std::vector<gpspoint> &array) {
	char buff[1024];
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "file open failed.\n");
		return 0; // failed
	}
	char tstr[1024];
	double t, la, lo;
	while (fgets(buff, 1024, fp) != NULL) {
		sscanf(buff, "%[^,],%lf,%lf", tstr, &la, &lo);
		t = atof(tstr);
		array.push_back(gpspoint(t, la, lo));
	}
	fclose(fp);
	return 1; // succeeded
}

int main(int argc, char **argv) {
	if (!(argc > 2)) {
		fprintf(stderr, "two file names requested.\n");
		return EXIT_FAILURE;
	}
	std::vector<gpspoint> parray, qarray;
	read_gpspoint_csv(argv[1], parray);
	read_gpspoint_csv(argv[2], qarray);

	printf("\n%s:\n", argv[1]);
	printf("%lu points.\n", parray.size());
#ifdef SHOW_SEQ
	for(int i = 0; i < parray.size(); ++i) {
		printf("%d: %lf, %lf, %lf", i, parray[i].time, parray[i].lat, parray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", parray[i-1].distanceTo(parray[i]));
		printf("\n");
	}
#endif
	printf("%s:\n", argv[2]);
	printf("%lu points.\n", qarray.size());
#ifdef SHOW_SEQ
	for(int i = 0; i < qarray.size(); ++i) {
		printf("%d: %lf, %lf, %lf",
				i, qarray[i].time, qarray[i].lat, qarray[i].lon);
		if ( i > 0 )
			printf("; (%lf)", qarray[i-1].distanceTo(qarray[i]));
		printf("\n");
	}
#endif

	std::pair<int, std::vector<gpspoint::uintpair>> result = gpspoint::lcs(parray, qarray, 33);
	printf("\nthe length of a lcs: %d\n\n", result.first);
	for (auto i = result.second.begin(); i != result.second.end(); ++i) {
		int16_t iq = i->first, ip = i->second;
		if ( iq & 1 ) {
			printf("%d-%d ([%lf, %lf]-[%lf, %lf]) ", iq>>1, (iq>>1)+1, qarray[iq>>1].lat, qarray[iq>>1].lon, qarray[iq>>1].lat, qarray[(iq>>1)+1].lon);
		} else {
			printf("%d ([%lf, %lf]) ",  iq>>1, qarray[iq>>1].lat, qarray[(iq>>1)+1].lon);
		}
		if ( ip & 1 ) {
			printf(", %d-%d ([%lf, %lf]-[%lf, %lf]) ", ip>>1, (ip>>1)+1, parray[ip>>1].lat, parray[ip>>1].lon, parray[ip>>1].lat, parray[(ip>>1)+1].lon);
		} else {
			printf(", %d ([%lf, %lf]) ",  ip>>1, parray[ip>>1].lat, parray[(ip>>1)+1].lon);
		}
		if ( (iq & 1) == 0 && (ip & 1) == 0 ) {
			printf("%lf", qarray[iq>>1].distanceTo(parray[ip>>1]) );
		} else if ( (iq & 1) == 0 && (ip & 1) == 1 ) {
			printf("%lf", qarray[iq>>1].distanceTo(parray[ip>>1],parray[(ip>>1)+1]) );
		} else if ( (iq & 1) == 1 && (ip & 1) == 0 ) {
			printf("%lf", parray[ip>>1].distanceTo(qarray[iq>>1],qarray[(iq>>1)+1]) );
		} else {
			printf("error!");
		}
		printf("\n");
	}
	std::cout << std::endl << std::endl;

	/* write in csv format */
	/*
	for (auto i = result.second.begin(); i != result.second.end(); ++i) {
		gpspoint p = parray[i->first];
		printf("%lf,%lf,%lf\n", p.time, p.lat, p.lon);
	}
	printf("\n");
	*/
	return EXIT_SUCCESS; // return 0;
}
