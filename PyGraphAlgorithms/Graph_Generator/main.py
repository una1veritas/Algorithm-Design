'''
Created on 2025/07/01

@author: sin
'''
import networkx as nx
import matplotlib.pyplot as plt

if __name__ == '__main__':

    # Example: create a random graph
    G = nx.erdos_renyi_graph(20, 0.4)
    
    print("G.nodes = ", G.nodes)
    print("G.edges = ", G.edges)

    hub_cover = set()
    edge_covered = set()
    while set(G.nodes) != edge_covered :
        best = None
        best_covered = set()
        for v in set(G.nodes) - hub_cover :
            new_covered = [(u,w) for (u,w) in set(G.edges) - edge_covered if u == v or w == v or (G.has_edge(u,v) and G.has_edge(w,v) )]
            if best is None or len(new_covered) > len(best_covered) :
                best = v
                best_covered = new_covered
        
        print(v, best_covered)
        break
    
    # Draw the graph
    nx.draw(G, with_labels=True, node_color='lightgrey')  # with_labels=True adds node labels
    plt.show()  # This opens a window with the plot

