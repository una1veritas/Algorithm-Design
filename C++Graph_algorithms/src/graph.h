/*
 * SimpleGraph.c
 *
 *  Created on: 2023/01/08
 *      Author: Sin Shimozono
 */

#ifndef GRAPH_H_
#define GRAPH_H_

// 辺重み付き単純グラフ

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cinttypes>

typedef uint64_t Vertex;

struct Edge {
	Vertex src, dst;
	double weight;

	bool operator==(const Edge & other) const {
		return (src == other.src and dst == other.dst) or (src == other.dst and dst == other.src);
	}

	size_t hash() const {
		return std::hash<Vertex>()(src) ^ std::hash<Vertex>()(dst) ;
	}

	friend std::ostream & operator<<(std::ostream & out, const Edge & e) {
		out << "(" << e.src << ", " << e.dst << "; " << e.weight << ")";
		return out;
	}
};

template<>
struct std::hash<Edge>{
	public:
	std::size_t operator () ( const Edge &e ) const noexcept {
		return e.hash() ;
	}
};


// 単純辺重みつきグラフ型
struct Graph {
	std::unordered_set<Vertex> vertices;
	std::unordered_set<Edge> edges;

	Graph(std::vector<Vertex> & vset, std::vector<Edge> & eset) {
		if ( vset.size() > 0 ) {
			for(const auto & v : vset) {
				vertices.insert(v);
			}
			for(const auto & e : eset) {
				if ( vertices.contains(e.src) and vertices.contains(e.dst)) {
					edges.insert(e);
				}
			}
		}
		return;
	}

	Graph(std::vector<Vertex> & vset, std::pair<Vertex,Vertex> & eset, std::vector<double> & ) {
		if ( vset.size() > 0 ) {
			for(const auto & v : vset) {
				vertices.insert(v);
			}
			for(const auto & e : eset) {
				if ( vertices.contains(e.src) and vertices.contains(e.dst)) {
					edges.insert(e);
				}
			}
		}
		return;
	}

	Graph() {}
/*
 * int Graph_has_vertex(Graph * gp, Vertex a);
int Graph_adjacent(Graph * gp, Vertex a, Vertex b);
int Graph_edge_weight(Graph * gp, Vertex a, Vertex b);
int Graph_adjacent_directed(Graph * gp, Vertex a, Vertex b);
void Graph_add_vertex(Graph * gp, int v);
// 無向辺の追加
void Graph_add_edge(Graph * gp, Edge e);
// 有向辺の追加
void Graph_add_directed_edge(Graph * gp, Edge e);
void Graph_print(Graph * gp);
 */
};

#endif /* SIMPLEGRAPH_H_ */
