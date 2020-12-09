import random
f = open("test.txt",'w')
for i in range(0,100):
    x = random.randint(1,50)
    f.write(str(x))
    f.write(" ")
    y = random.randint(1,50)
    f.write(str(y))
    if i < 99:
        f.write(",")

f.close()
