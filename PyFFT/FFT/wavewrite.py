import math

pf = 'data.txt'
data = list()
window = 64
period = window / 4
for i in range(window):
    val = math.sin((2*math.pi*i+10)/period) 
    #val = ((i % period) - period/2)/period
    data.append(val)

with open(pf, mode='w') as f:
    for d in data:
        f.write(str(d))
        f.write('\n')
        
print()
for d in data:
    print(d)