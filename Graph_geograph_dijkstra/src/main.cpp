//============================================================================
// Name        : geograph_sample.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <algorithm>
#include <limits>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "geograph.h"
#include "bgeohash.h"

using namespace std;


vector<string> split(string& input, char delimiter) {
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int show_in_sdl_window(const geograph & map, const std::vector<geopoint> & route);

std::pair<std::vector<uint64_t>, double> shortest_path(const geograph & map, const geopoint & startpoint, const geopoint & goalpoint) {
	cout << "shortest_path" << std::endl;
    std::set<uint64_t> vertices;  // the set of OSM IDs.
    for(const auto & itr : map.nodemap() ) {
    	vertices.insert(itr.first);
    }
    cout << "vertices size = " << dec << vertices.size() << endl;

    // 大学の前から新飯塚駅の入り口まで
    //geopoint start_coord(33.651759, 130.672120);
    //geopoint goal_coord(33.644224, 130.693827);
    // 大学の前からバスセンターまで
    //geopoint start_coord(33.651759, 130.672120);
    //geopoint goal_coord(33.64119, 130.68598);

    // find the nearest points corresponds to the start and the goal.
    uint64_t osmid_start = map.node_nearest_to(startpoint).id();
	uint64_t osmid_goal = map.node_nearest_to(goalpoint).id();
    cout << "start point = " << map.node(osmid_start) << " id " << std::dec << osmid_start << endl;
    cout << "goal point = " << map.node(osmid_goal) << " id " << std::dec << osmid_goal << endl;

    // Dijkstra's algorithm to compute the length of shortest path to the nodes
    //
    // use vertices as the set (V - P) of remained (still not visited) vertices.
    // label (mapping) from vertices to the distance of the shortest path.
    std::map<uint64_t, double> el;
    for(const auto & id : vertices) {
    	el[id] = std::numeric_limits<double>::infinity();  // initialize as +infinity
    }

    //int c = 0;
    el[osmid_start] = 0;
    while ( vertices.size() > 0 ) {
    	// find the point u to which the path is shortest
    	double elmin = std::numeric_limits<double>::infinity();
    	uint64_t u = 0;
    	for(const auto & osmid : vertices) {
    		if ( el[osmid] < elmin ) {
    			u = osmid;
    			elmin = el[osmid];
    		}
    	}
    	//cout << "nearest u = " << u << ", el[u] = " << el[u] << endl;
    	if (u == 0)
    		break; // unreachable points?
    	vertices.erase(u);  // the dist. of the shortest path to u is determined.
    	if (u == osmid_goal)
    		break;
    	// for each point adjacent to u and in vertices
    	//cout << "update adjacents. " << endl;
    	for(const auto & v : map.adjacent_nodes(u) ) {
			if ( vertices.contains(v) ) {  // C++20
    			double dist_uv = map.point(u).distance_to(map.point(v));
    			if ( el[v] > el[u] + dist_uv ) {
    				el[v] = el[u] + dist_uv;
    			}
    		}
    	}
    }

    // find the shortest path from the start to the goal by back-tracking
    vector<uint64_t> path;
    path.push_back(osmid_goal);
    uint64_t curr_id = osmid_goal;
    while (curr_id != osmid_start) {
    	for(const auto & adj : map.adjacent_nodes(curr_id) ) {
			double dist = map.point(adj).distance_to(map.point(curr_id));
			if ( el[curr_id] == el[adj] + dist ) {
				curr_id = adj;
				path.push_back(adj);
			}
    	}
    }

    /*
    std::vector<geopoint> route;
    for(auto ritr = path.crbegin(); ritr != path.crend(); ritr++ ) {
    	cout << *ritr << " -> ";
    	route.push_back(map.point(*ritr));
    }
    cout << endl;

    cout << "distance from the start to the goal is " << el[osmid_goal] << endl;
    */
    std::reverse(path.begin(), path.end());

    return std::pair<std::vector<uint64_t>, double>(path, el[osmid_goal]);
}

int main(int argc, char * argv[]) {
	ifstream csvf;

	if (argc < 2) {
		cerr << "usage: command map-file_name]" << endl;
		exit(EXIT_FAILURE);
	}

	cout << "reading geograph file " << argv[1] << ". " << endl;
	csvf.open(argv[1]);
	if (! csvf ) {
		cerr << "open a geograph file " << argv[1] << " failed." << endl;
		exit(EXIT_FAILURE);
	}
	geograph ggraph;
    string line;
    while (getline(csvf, line)) {
        vector<string> strvec = split(line, ',');
        if (strvec.size() < 4) {
        	cerr << "insufficient parameters to define a node_edge." << endl;
        	continue;
        }
		uint64_t id = stoull(strvec[0]);
		double lat = stod(strvec[1]);
		double lon = stod(strvec[2]);
        vector<uint64_t> adjacents;
        for(unsigned int i = 3; i < strvec.size(); ++i)
        	adjacents.push_back(stoull(strvec[i]));
        ggraph.insert(id, lat, lon, adjacents);
        adjacents.clear();
    }
    csvf.close();

    cout << "goegraph node size = " << dec << ggraph.size() << endl;


    geopoint start_coord(33.651759, 130.672120), goal_coord(33.644224, 130.693827);
    std::pair<std::vector<uint64_t>, double> path = shortest_path(ggraph, start_coord, goal_coord);

    std::vector<geopoint> route;
    for(auto & id : path.first) {
    	route.push_back(ggraph.point(id));
    }
    show_in_sdl_window(ggraph, route);

    return EXIT_SUCCESS;
}

int show_in_sdl_window(const geograph & map, const std::vector<geopoint> & route) {
	constexpr unsigned int WINDOW_MIN_WIDTH = 1024;
	constexpr unsigned int WINDOW_MIN_HEIGHT = 768;
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	union Color {
		struct {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
		uint32_t color;

		Color() : r(0), g(0), b(0), a(0xff) {}
		Color(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha = 0xff) : r(red), g(grn), b(blu), a(alpha) {}
		Color & operator()(uint8_t red, uint8_t grn, uint8_t blu, uint8_t alpha = 0xff) {
			r = red; g = grn; b = blu; a = alpha;
			return *this;
		}
	} c, c2;

	struct {
		unsigned int w, h;
	} winrect = {WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT};

	georect area(route);
	//cout << traj_area.width_meter() << ", " << traj_area.height_meter() << endl;
	// pixel per degree
	double vscale, hscale;
	if ( area.width_meter() >= area.height_meter()) {
		hscale = 0.75 * double(WINDOW_MIN_WIDTH) / (area.west - area.east);
		vscale = 0.75 * double(WINDOW_MIN_WIDTH) / area.aspect_ratio() / (area.north - area.south);
	} else {
		vscale = 0.75 * double(WINDOW_MIN_HEIGHT) / (area.north - area.south);
		hscale = 0.75 * double(WINDOW_MIN_HEIGHT) * area.aspect_ratio() / (area.west - area.east);
	}
	georect viewarea(area);
	cout << "hscale = " << hscale << ", vscale = " << vscale << endl;
	if ( (SDL_Init( SDL_INIT_VIDEO ) < 0)
			or !(window = SDL_CreateWindow( "Geograph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					winrect.w, winrect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
			or !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE)) ) {
		cerr << "Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	} else {
		int mx0 = 0, my0 = 0, mx1 = 0, my1 = 0;
		double diff_h = 0, diff_v = 0;
		Color c, c2;
		bool quit = false;
		bool update = true;
		bool show_track = true;
		bool dragging = false;
		SDL_Event event;
		while (!quit) {
			SDL_Delay(10);
			SDL_PollEvent(&event);
			switch (event.type)	{
				case SDL_QUIT:
					quit = true;
					break;
				// TODO input handling code goes here
				case SDL_MOUSEMOTION:
					if (dragging and
							(mx1 != event.button.x or my1 != event.button.y)) {
						mx1 = event.button.x;
						my1 = event.button.y;
						update = true;
						//cout << mx1 << ",  " << my1 << endl;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (show_track == true ) {
						show_track = false;
						update = true;
					}
					dragging = true; // start dragging
					mx0 = event.button.x;
					my0 = event.button.y;
					mx1 = mx0; my1 = my0;
					break;
				case SDL_MOUSEBUTTONUP:
					if (mx0 != mx1 or my0 != my1) {
						diff_h = (mx1 - mx0) / hscale;
						diff_v = (my1 - my0) / vscale;
						mx0 = mx1; my0 = my1;
						viewarea.shift(diff_v, -diff_h);
						update = true;
					}
					if ( show_track == false ) {
						show_track = true;
						update = true;
					}
					dragging = false; // finish dragging
					break;
				case SDL_WINDOWEVENT:
					// resize function is still incomplete;
					// map-drawing of enlarged area is postponed
					// after the succeeding resize.
					/*
					switch (event.window.event) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						winrect.w = event.window.data1;
						winrect.h = event.window.data2;
						//cout << "CHANGED " << winrect.h << ", " << winrect.w << endl;
						//break;
					//case SDL_WINDOWEVENT_RESIZED:
						update = true;
						//cout << "RESIZED" << endl;
						viewarea.south = viewarea.north - double(winrect.h) / vscale;
						viewarea.west = viewarea.east + double(winrect.w) / hscale;
						break;
					}
					*/
				break;
			}

			// TODO rendering code goes here
			if ( update ) {
				// clear window
				Color c, c2;
				c(242, 242, 242);
				SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
				SDL_RenderClear(renderer);
				//cout << mx0 << ", " << my0 << "; " << mx1 << ", " << my1 << endl;
				// tweak the view rect
				diff_h = (mx1 - mx0) / hscale;
				diff_v = (my1 - my0) / vscale;
				georect drawrect(viewarea);
				drawrect.shift(diff_v, -diff_h);

				for(auto itr = map.cbegin(); itr!= map.cend(); ++itr) {
					const geopoint & p = itr->second.point();
					if ( drawrect.contains(p) ) {
						int x0 = (p.lon - drawrect.east) * hscale;
						int y0 = (drawrect.north - p.lat) * vscale;
						//cout << p << " " << hscale << " " << vscale << endl;
						c(192,192,192);
						c2(64,64,64);
						filledCircleColor(renderer, x0, y0, 1, c.color);
						for(auto & adjid : map.adjacent_nodes(itr->first)) {
							int x1 = (map.node(adjid).point().lon - drawrect.east) * hscale;
							int y1 = (drawrect.north - map.node(adjid).point().lat) * vscale;
							filledCircleColor(renderer, x1, y1, 1, c2.color);
							lineColor(renderer, x0, y0, x1, y1, c.color);
							//cout << x0 << ", " << y0 << "; " << x1 << ", " << y1 << endl;
						}
					}
				}

				if ( show_track ) {
					for(unsigned int i = 0; i < route.size() - 1; ++i ) {
						if ( drawrect.contains(route[i]) ) {
							int x0 = (route[i].lon - drawrect.east) * hscale;
							int y0 = (drawrect.north - route[i].lat) * vscale;
							c(0,0,0x7f);
							filledCircleColor(renderer, x0, y0, 2, c.color);
							int x1 = (route[i+1].lon - drawrect.east) * hscale;
							int y1 = (drawrect.north - route[i+1].lat) * vscale;
							filledCircleColor(renderer, x0, y0, 2, c.color);
							lineColor(renderer, x0, y0, x1, y1, c.color);
						}
					}
				}

				SDL_RenderPresent(renderer);
				update = false;
			}
		}
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
	return EXIT_SUCCESS;
}
