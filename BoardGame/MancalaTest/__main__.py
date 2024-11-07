import random 

class Mancala:
    def __init__(self, numberOfPlayers = 2, numberOfHoles = 7,numberOfStores = 1, numberOfStones = 3):
        self.nplayers = numberOfPlayers
        self.nholes = numberOfHoles
        self.nstores = numberOfStores
        self.nstones = numberOfStones
        self.board = list()
        for i in range(self.nplayers):
            self.board.append([self.nstones if i < self.nholes - self.nstores else 0 \
                               for i in range(self.nholes)])
    
    def __copy__(self):
        newcopy = Mancala(self.nplayers, self.nholes, self.nstores, self.nstones)
        newcopy.board = list()
        for pix in range(self.nplayers):
            newcopy.board.append([e for e in self.board[pix]])
        return newcopy
    
    def __str__(self):
        s = ''
        for pix in range(self.nplayers):
            s += '['
            if self.nholes - self.nstores > 0 :
                s += str(self.board[pix][0])
                for hix in range(1,self.nholes):
                    if hix != self.nholes - self.nstores:
                        s += ', '
                    else:
                        s += '; '
                    s += str(self.board[pix][hix])
            s += '] '
        return s
    
    def possible_choices(self, turn):
        turn %= self.nplayers
        return [ix for ix in range(m.nholes - m.nstores) if m.board[turn][ix] > 0]
    
    def mancala_basic_move(self, turn, choice):
        turn %= self.nplayers
        if not (0 <= choice <= self.nholes - self.nstores) :
            raise ValueError('Error: incorrect choice.')
        seedstaken = self.board[turn][choice]
        if seedstaken == 0 :
            raise ValueError('Error: an empty hole is chosen.')
        #print('turn, choice, seedstaken = ', turn, choice, seedstaken)
        self.board[turn][choice] = 0
        index = turn * self.nholes + choice
        last_index = index
        #print("starting index = ", index)
        for pos in range(index + 1, index + 1 + seedstaken):
            #print( (pos // self.nholes) % self.nplayers, pos % self.nholes)
            self.board[(pos // self.nholes) % self.nplayers][pos % self.nholes] += 1
            last_index = pos % (self.nplayers * self.nholes)
        #print("last ", last_index, last_index % self.nholes)
        if last_index % self.nholes >= self.nholes - self.nstores :
            return True
        else:
            return False
        
    def won_by(self):
        for plix in range(self.nplayers) :
            if sum(self.board[plix][:self.nholes - self.nstores]) == 0 :
                return plix
        return -1


m = Mancala()
turn = 0
while True:
    print(m)
    if (win := m.won_by()) >= 0 :
        break
    choices = m.possible_choices(turn)
    if len(choices) == 0 : break
    choice = choices[random.randrange(len(choices))]
    #print(choices, choice)
    print('turn, choice = {}, {}'.format(turn, choice))
    turn_continue = m.mancala_basic_move(turn, choice)
    if turn_continue:
        print('player {}\'s turn continues.'.format(turn))
        continue
    print('change turn to player {}.'.format(turn))
    turn = (turn + 1) % m.nplayers
    
print('won by player '+str(win))