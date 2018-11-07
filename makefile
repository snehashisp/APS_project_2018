CC=g++

main: node.o Binomial-Heap.o fibonacci.o van_emde.o main.cpp
	$(CC) -O3 -o main main.cpp Binomial-Heap.o fibonacci.o van_emde.o node.o
