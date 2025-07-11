'''
Created on 2025/07/11

@author: sin
'''

import networkx as nx
import matplotlib.pyplot as plt

if __name__ == '__main__':
    
    plt.ion()  # Interactive mode
    
    fig, ax = plt.subplots()
    
    for i in range(5):
        G = nx.gnp_random_graph(10, 0.3)  # Generate a random graph
        ax.clear()  # Clear previous drawing
        nx.draw(G, ax=ax, with_labels=True)
        plt.draw()
        plt.pause(1)  # Pause to update the plot (1 second here)
    
    plt.ioff()
    plt.show()