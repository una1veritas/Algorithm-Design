// C program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
//
// modified as a pure C code by Sin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simplegraph.h"

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
void KruskalMST(struct Graph* graph)
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
	struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));

	// Create V subsets with single elements
	for (int v = 0; v < V; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1
	while (e < V - 1 && i < graph->E) {
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

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
			result[i].dest, result[i].weight);
		minimumCost += result[i].weight;
	}
	printf("Minimum Cost Spanning tree : %d",minimumCost);
	return;
}

// Driver program to test above functions
int main()
{
	/* Let us create following weighted graph
			10
		0--------1
		| \	 |
		6| 5\ |15
		|	 \ |
		2--------3
			4	 */
	int V = 4; // Number of vertices in graph
	int E = 5; // Number of edges in graph
	struct Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 10;

	// add edge 0-2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	// add edge 0-3
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	// add edge 1-3
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	// add edge 2-3
	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	KruskalMST(graph);

	free(graph);
	return 0;
}
