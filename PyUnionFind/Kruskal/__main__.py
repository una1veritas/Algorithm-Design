'''
Created on Jul 14, 2025

@author: sin
'''
import networkx as nx
import itertools
import random
import matplotlib.pyplot as plt

def min_spanning_tree(g: nx.Graph):
    q = sorted([(u, v, ddict['weight']) for (u, v, ddict) in g.edges(data=True)], key=lambda x: x[2])
    edges = set()
    vgroups = [ {i} for i in G.nodes]
    #print(edges, vgroups)
    for (u,v,w) in q:
        for i in range(len(vgroups)):
            if u in vgroups[i] :
                uix = i
            if v in vgroups[i] :
                vix = i
        if uix != vix :
            #print((u,v), uix, vix, len(vgroups))
            edges.add( (u,v,w) )
            if uix < vix :
                vgroups[uix] = vgroups[uix].union(vgroups[vix])
                del vgroups[vix]
            else:
                vgroups[vix] = vgroups[uix].union(vgroups[vix])
                del vgroups[uix]
            #print(edges, vgroups)
    t = nx.Graph()
    t.add_nodes_from(g.nodes)
    t.add_edges_from([(u, v, {'weight':w})for u,v,w in edges])
    return t

if __name__ == '__main__':
    
    plt.ion()  # Interactive mode
    fig, ax = plt.subplots()
    
    for n in range(6,100):
        for i in range(1):
            # Example: create a random graph
            G = nx.erdos_renyi_graph(n, 0.4)
            #G = nx.connected_watts_strogatz_graph(n=n, k=6, p=0.35)
            #G = nx.barabasi_albert_graph(n, 5)
            for e in G.edges:
                rn = random.uniform(0.5, 5.0)
                G[e[0]][e[1]]['weight'] = round(rn,2)
            # for u, v, data in G.edges(data=True):
            #     print(f"Edge {u}-{v} has weight {data['weight']}")
            T = min_spanning_tree(G)
            pos = nx.spring_layout(G, weight='weight')
            ax.clear()
            e_colors = ['black' if e in T.edges else 'lightgray' for e in G.edges]
            nx.draw(G, pos, ax=ax, with_labels=True, edge_color=e_colors, node_color=['lightgray'])
            plt.draw()
            plt.pause(1)  # Pause to update the plot (1 second here)

    
    plt.ioff()
    plt.show()
    
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

