'''
Created on 2025/07/01

@author: sin
'''
import networkx as nx
import itertools
import matplotlib.pyplot as plt

def covered_by_hub(g : nx.Graph, node : int):
    hcov = set()
    for v in g.neighbors(node):
        if v < node :
            hcov.add( (v, node) )
        else:
            hcov.add( (node, v) )
    for (u, v) in itertools.combinations(g.neighbors(node), 2):
        if g.has_edge(u,v) :
            hcov.add( (u, v) )
    return hcov

def is_hub_cover(g: nx.Graph, nodeset : set):
    edges = list(g.edges())
    for v in nodeset:
        if v not in g.nodes() :
            print('unknown node exists: ' + str(v))
            continue
        edges = [(u, w) for (u, w) in edges \
                 if (u != v and w != v) and not (g.has_edge(u, v) and g.has_edge(w, v))]
    return len(edges) == 0

def find_min_hub_cover(g : nx.Graph):
    for n in range(1,len(g)):
        for nsubset in itertools.combinations(set(G.nodes), n):
            if is_hub_cover(G, nsubset):
                return nsubset
    return None
            
def node_set(edges):
    nodes = set()
    for u, v in edges:
        nodes.add(u)
        nodes.add(v)
    return nodes
    
def greedy_Hub_Cover(g, weight=None):
    hub_cover = set()
    node_remained = set(g.nodes)
    edge_remained = set(g.edges)
    edge_covered = set()
    while len(edge_remained) > 0 :
        #print(hub_cover, edge_remained)
        # find the best node
        best_node = None
        best_cost = 0
        best_covered = set()
        for v in node_remained :
            new_covered = covered_by_hub(g, v) - edge_covered
            if len(new_covered) == 0 :
                continue
            cost = 1/len(new_covered)
            if weight is not None:
                cost = weight[v]/len(new_covered) 
            if best_node is None or cost < best_cost :
                best_node = v
                best_cost = cost
                best_covered = new_covered
                
        # add to cover and merge newly covered edges
        hub_cover.add(best_node)
        node_remained.remove(best_node)
        edge_covered = edge_covered.union(best_covered)
        edge_remained = edge_remained - best_covered
    return hub_cover
    
if __name__ == '__main__':

    for n in range(16,100):
        for i in range(1):
            # Example: create a random graph
            G = nx.erdos_renyi_graph(n, 0.25)
            minhubcover = find_min_hub_cover(G)
            print(len(minhubcover), minhubcover)                        

            res1 = greedy_Hub_Cover(G)
            print(f'size of graph = {len(G.nodes)}, edge-vertex ratio = {round(len(G.edges)/len(G.nodes),2)}, perf. ratio = {len(res1)/len(minhubcover)}' )
    
    exit()
    color_list = []
    for v in G.nodes:
        if v in res2:
            color_list.append('skyblue')
        else:
            color_list.append('lightgray')
    # Draw the graph
    nx.draw(G, with_labels=True, node_color=color_list)  # with_labels=True adds node labels
    plt.show()  # This opens a window with the plot

