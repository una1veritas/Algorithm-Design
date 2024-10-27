

class Mancala:
    def __init__(self, npits, nstones):
        self.board = list()
        for i in range(2):
            self.board.append(list())
            for j in range(npits - 1) :
                self.board[-1].append(nstones)
            self.board[-1].append(0)
    
    
m = Mancala(7, 3)
print(m.board)
