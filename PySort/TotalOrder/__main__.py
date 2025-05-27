'''
Created on 2025/05/13

@author: sin
'''

class Member:
    def __init__(self, mid, name, age, gender ):
        self.mid = int(mid)
        self.name = str(name)
        self.age = int(age),
        self.gender = str(gender)[0]
    
    def __str__(self):
        return f'Member(mid={self.mid}, name={self.name}, age={self.age}, gender={self.gender})'
    
if __name__ == '__main__':
    members = list()
    members.append(Member(1, 'Tom', 13, 'M'))
    members.append(Member(2, 'Jill', 14, 'F'))
    members.append(Member(3, 'George', 11, 'M'))
    
    for m in members:
        print(m)
    
    print('Bye.')