
class Mancala:
    def __init__(self, numberOfPlayers = 2, numberOfHoles = 7, numberOfStones = 3, numberOfStores = 1):
        self.nplayers = numberOfPlayers
        self.nholes = numberOfHoles
        self.nstones = numberOfStones
        self.nstores = numberOfStores
        self.board = list()
        for i in range(self.nplayers):
            self.board.append([self.nstones if i < self.nholes - self.nstores else 0 \
                               for i in range(self.nholes)])
    
    def mancala_basic_move(self, turn, choice):
        if not (1 <= turn <= self.nplayers) :
            raise ValueError('Error: incorrect turn in move.')
        if not (1 <= choice <= self.nholes - self.nstores) :
            raise ValueError('Error: incorrect choice in move.')
        seedstaken = self.board[turn - 1][choice - 1]
        if seedstaken == 0 :
            raise ValueError('Error: an empty pit is chosen in move.')
        print('turn, choice = ', turn, choice)
        self.board[turn - 1][choice - 1] = 0
        index = (turn - 1) * self.nholes + (choice - 1)
        last_index = index
        print("starting index = ", index)
        for pos in range(index + 1, index + 1 + seedstaken):
            print(pos // self.nholes, pos % self.nholes)
            self.board[pos // self.nholes][pos % self.nholes] += 1
            last_index = pos
        print("last ", last_index, last_index % self.nholes)
        if last_index % self.nholes >= self.nholes - self.nstores :
            return True
        else:
            return False

m = Mancala()
print(m.board)
print(m.mancala_basic_move(1, 2))
print(m.board)
print(m.mancala_basic_move(2, 4))
print(m.board)
