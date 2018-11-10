import sys
import tkinter
import matplotlib.pyplot as plt


filename = sys.argv[1]
fp = open(filename,"r")

vebt = [0]*101
fibo = [0]*101
bino = [0]*101

vebtype = [0]*101
xarr = list(range(0,101))

line = fp.readline()
while line != '':
    temp = line.split(" ")
    xpos = int(int(temp[0]) / 10)
    vebtype[xpos] = int(temp[1])
    vebt[xpos] = float(temp[2])
    fibo[xpos] = float(temp[3])
    bino[xpos] = float(temp[4])
    line = fp.readline()

fp.close()

plt.plot(xarr,vebt)
plt.plot(xarr,bino)
plt.plot(xarr,fibo)
plt.show()




