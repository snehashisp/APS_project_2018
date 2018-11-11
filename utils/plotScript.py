import sys
import tkinter
import matplotlib.pyplot as plt


filename = sys.argv[1]
fp = open(filename,"r")

vebt = [0]*101
fibo = [0]*101
bino = [0]*101

vebtype = [0]*101
xarr = list(range(0,1001,10))

line = fp.readline()
while line != '':
    temp = line.split(" ")
    xpos = int(int(temp[0])/10)
    #xpos = int((int(temp[0])-2000) / 100)
    vebtype[xpos] = int(temp[1])
    vebt[xpos] = float(temp[2])
    fibo[xpos] = float(temp[3])
    bino[xpos] = float(temp[4])
    line = fp.readline()

fp.close()

plt.figure(num=None, figsize=(10,6), dpi=160, facecolor = "w", edgecolor = "k")
plt.plot(xarr,vebt,label = "vEB Tree")
plt.plot(xarr,bino,label = "binomial")
plt.plot(xarr,fibo,label = "fibonacci")

plt.xlabel('nodes in graph')
plt.ylabel('execution tim')
plt.title(str(sys.argv[3]) + '% density node graph')
plt.legend()

plt.savefig("graphs/Fig_" + str(sys.argv[2]) + str(sys.argv[3]))




