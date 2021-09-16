//============================================================================
// Name        : Line_Point_matching.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#include <cmath>

using namespace std;

struct Point {
	double x, y;

	Point(const double & _x, const double & _y) : x(_x), y(_y) {}

	Point operator-(const Point & b) const{
		return Point(x - b.x, y - b.y);
	}

	double distanceto(const Point & q) const {
		double dx = x - q.x, dy = y - q.y;
		return sqrt(dx*dx + dy*dy);
	}

	double norm_outer_prod(const Point & p, const Point & q) const {
		Point op(p - *this), oq(q - *this);
		return (op.x * oq.y) - (op.y * oq.x);
	}

	double norm_inner_prod(const Point & p, const Point & q) const {
		Point op(p - *this), oq(q - *this);
		return (op.x * oq.x) + (op.y * oq.y);
	}

	friend std::ostream & operator<<(std::ostream & out, const Point & me) {
		out << me.x << ", " << me.y;
		return out;
	}
};

struct Line {
	Point from, to;

	Line(const Point & f, const Point & t) : from(f), to(t) {}
	Line(const double & _x0, const double & _y0, const double & _x1, const double & _y1) :
		from(_x0, _y0), to(_x1, _y1) {}

	double length() const {
		return from.distanceto(to);
	}

	double distanceto(const Point & p) const {
		if ( to.norm_inner_prod(from, p) < 0 ) { // < 0.0
			return to.distanceto(p);
		}
		if ( from.norm_inner_prod(to, p) < 0 ) { // < 0.0
			return from.distanceto(p);
		}
		double d = from.norm_outer_prod(to, p) / length();
		if ( d < 0 )
			return -d;
		return d;
	}

	 double matching_point_distance(const Point & p, const double & proximity) {
		double len = length();
		if (len == 0)
			return 0;
		double parallel_dist = to.norm_outer_prod(from, p) / length();
		return parallel_dist;
	}

	friend std::ostream & operator<<(std::ostream & out, const Line & me) {
		out << me.from.x << ", " << me.from.y << " - "
				<< me.to.x << ", " << me.to.y;
		return out;
	}
};

int read_csv(istream & ifile, std::vector<std::vector<std::string>> &tbl);

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	vector<vector<string>> tbl;
	vector<Line> lines;
	vector<Point> points;

	ifstream linesfile("lines.csv");
	read_csv(linesfile, tbl);
	for(auto row = tbl.begin(); row != tbl.end(); ++row) {
		double x0 = stod((*row)[0]), y0 = stod((*row)[1]), x1 = stod((*row)[2]), y1 = stod((*row)[3]);
		lines.push_back(Line(x0, y0, x1, y1));
	}
	linesfile.close();
	tbl.clear();
	ifstream pointsfile("points.csv");
	read_csv(pointsfile, tbl);
	for(auto row = tbl.begin(); row != tbl.end(); ++row) {
		double x0 = stod((*row)[0]), y0 = stod((*row)[1]);
		points.push_back(Point(x0, y0));
	}
	pointsfile.close();

	std::cout << "lines" << std::endl;
	for(auto p = lines.begin(); p != lines.end(); ++p)
		std::cout << *p <<std::endl;
	std::cout << std::endl << "points" << std::endl;
	for(auto p = points.begin(); p != points.end(); ++p)
		std::cout << *p << std::endl;
	std::cout <<std::endl;

	Line & l = lines[0];
	Point & p = points[0];
	std::cout << l.length() << std::endl;
	std::cout << l.distanceto(p) << std::endl;
	std::cout << l.matching_point_distance(p, 0.5) << std::endl;
	return 0;
}

int read_csv(istream & ifile, std::vector<std::vector<std::string>> &tbl) {
	if ( !ifile ) {
		fprintf(stderr, "file open failed.\n");
		return 0; // failed
	}
	std::istringstream strin;
	std::string buf;
	size_t fromindex, toindex;
	while (! ifile.eof()) {
		getline(ifile, buf, '\n');
		if ( buf.empty() )
			continue;
		tbl.push_back(std::vector<std::string>());
		//std::cout << buf << std::endl;
		unsigned int field;
		for (fromindex = 0, field = 0; fromindex < buf.size(); fromindex = toindex + 1, ++field) {
			toindex = buf.find_first_of(",", fromindex + 1);
			if ( toindex == std::string::npos ) {
				toindex = buf.size();
			}
			std::string sub(buf, fromindex, toindex - fromindex);
			//std::cout << "[" << fromindex << ", " << toindex << "] " << sub << ", ";
			tbl.back().push_back(sub);
		}
		//std::cout << std::endl;
	}
	return 1; // succeeded
}
