'''
Created on 2025/07/01

@author: sin
'''
import networkx as nx
import itertools
import matplotlib.pyplot as plt

def edges_hub_covered_by(g : nx.Graph, node : int):
    hcov = set()
    
    adjnodes = set(g.neighbors(node))
    for v in adjnodes:
        if v < node :
            hcov.add( (v, node) )
        else:
            hcov.add( (node, v) )
    for (u, v) in itertools.combinations(adjnodes, 2):
        if g.has_edge(u,v) :
            hcov.add( (u, v) )
    return hcov

def node_set(edges):
    nodes = set()
    for u, v in edges:
        nodes.add(u)
        nodes.add(v)
    return nodes
    
def greedy_Hub_Cover(g, node_weight = None):
    hub_cover = set()
    node_remained = set(g.nodes)
    edge_remained = set(g.edges)
    edge_covered = set()
    while len(edge_remained) > 0 :
        #print(hub_cover, edge_remained)
        # find the best node
        best_node = None
        best_gain = None
        best_covered = set()
        for v in node_remained :
            hcov_by_v = edges_hub_covered_by(g, v)
            new_covered = hcov_by_v - edge_covered
            if len(new_covered) == 0 :
                continue
            if node_weight == None :
                if best_node is None or len(new_covered) > len(best_covered) :
                    best_node = v
                    best_covered = new_covered
            else:
                if best_node is None or len(new_covered)/len(node_set(new_covered)) > best_gain :
                    best_node = v
                    best_covered = new_covered
                    best_gain = len(new_covered)/len(node_set(new_covered))
                
        # add to cover and merge newly covered edges
        hub_cover.add(best_node)
        node_remained.remove(best_node)
        edge_covered = edge_covered.union(best_covered)
        edge_remained = edge_remained - best_covered
    return hub_cover
    
if __name__ == '__main__':

    for n in range(16,100):
        for i in range(10):
            # Example: create a random graph
            G = nx.erdos_renyi_graph(n, 0.5)
            res = greedy_Hub_Cover(G)
            weight = dict()
            for v in G.nodes:
                weight[v] = len(node_set(edges_hub_covered_by(G, v))) + 1
            res_wv = greedy_Hub_Cover(G, weight)
            print(len(G.nodes), round(len(G.edges)/len(G.nodes),2), round(len(res)/len(G.nodes),2), round(len(res_wv)/len(G.nodes),2) )
    
    exit()
    color_list = []
    for v in G.nodes:
        if v in res:
            color_list.append('skyblue')
        else:
            color_list.append('lightgray')
    # Draw the graph
    nx.draw(G, with_labels=True, node_color=color_list)  # with_labels=True adds node labels
    plt.show()  # This opens a window with the plot

