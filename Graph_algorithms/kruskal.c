// C program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
//
// modified as a pure C code by Sin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SimpleGraph.h"
#include "UnionFind.h"

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int weight_descending(const void* a, const void* b)
{
	Edge* a1 = (Edge*)a;
	Edge* b1 = (Edge*)b;
	return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's
// algorithm
void KruskalMST(Graph* graph)
{
	int vsize = graph->vsize;
	Edge result[vsize]; // Tnis will store the resultant MST
	int e = 0; // An index variable, used for result[]
	int i = 0; // An index variable, used for sorted edges

	// Step 1: Sort all the edges in non-decreasing
	// order of their weight. If we are not allowed to
	// change the given graph, we can create a copy of
	// array of edges
	qsort(graph->edges, graph->esize, sizeof(graph->edges[0]), weight_descending);

	// Allocate memory for creating V ssubsets
	Subset* subsets = (Subset*)malloc(vsize * sizeof(Subset));

	// Create V subsets with single elements
	for (int v = 0; v < vsize; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1
	while (e < vsize - 1 && i < graph->esize) {
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		Edge next_edge = graph->edges[i++];

		int x = Find(subsets, next_edge.src);
		int y = Find(subsets, next_edge.dst);

		// If including this edge does't cause cycle,
		// include it in result and increment the index
		// of result for next edge
		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}

	// print the contents of result[] to display the
	// built MST
	printf(
		"Following are the edges in the constructed MST\n");
	int minimumCost = 0;
	for (i = 0; i < e; ++i)
	{
		printf("%d -- %d == %d\n", result[i].src,
			result[i].dst, result[i].weight);
		minimumCost += result[i].weight;
	}
	printf("Minimum Cost Spanning tree : %d",minimumCost);
	return;
}
