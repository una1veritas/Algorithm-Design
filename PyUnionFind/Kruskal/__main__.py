'''
Created on Jul 14, 2025

@author: sin
'''
import networkx as nx
#import itertools
import random
import matplotlib.pyplot as plt
from UnionFind import UnionFindN, UnionFindH, UnionFindC, UnionFindR

import time

def min_spanning_tree(g: nx.Graph):
    q = sorted([(u, v, ddict['weight']) for (u, v, ddict) in g.edges(data=True)], key=lambda x: x[2])
    edges = set()
    vgroups = UnionFindN(len(G.nodes))
    for (u,v,w) in q:
        uix = vgroups.find(u)
        vix = vgroups.find(v)
        if uix != vix :
            #print(vgroups)
            edges.add( (u,v,w) )
            vgroups.union(uix,vix)
    t = nx.Graph()
    t.add_nodes_from(g.nodes)
    t.add_edges_from([(u, v, {'weight':w})for u,v,w in edges])
    return t

if __name__ == '__main__':
    
    # plt.ion()  # Interactive mode
    # fig, ax = plt.subplots()
    graphs = list()
    exec_times = list()
    
    for n in range(4095,4096):
        for i in range(10):
            # Example: create a random graph
            G = nx.erdos_renyi_graph(n, 0.3)
            #G = nx.connected_watts_strogatz_graph(n=n, k=6, p=0.35)
            #G = nx.barabasi_albert_graph(n, 5)
            for e in G.edges:
                rn = random.uniform(0.5, 5.0)
                G[e[0]][e[1]]['weight'] = round(rn,2)
            # for u, v, data in G.edges(data=True):
            #     print(f"Edge {u}-{v} has weight {data['weight']}")
            graphs.append(G)
    
    for g in graphs:
        swatch_start = time.time()
        T = min_spanning_tree(g)
        swatch_end = time.time()
        exec_time = swatch_end - swatch_start
        exec_times.append(exec_time)
        print(f"Execution time: {exec_time}")
        # pos = nx.spring_layout(G, weight='weight')
        # ax.clear()
        # e_colors = ['black' if e in T.edges else 'lightgray' for e in G.edges]
        # nx.draw(G, pos, ax=ax, with_labels=True, edge_color=e_colors, node_color=['lightgray'])
        # plt.draw()
        # plt.pause(0.5)  # Pause to update the plot (1 second here)

    print(sum(exec_times)/len(exec_times))
    
    # plt.ioff()
    # plt.show()
    
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

