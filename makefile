CC=g++

main: node.o Binomial-Heap.o fibonacci.o van_emde.o main.cpp
	g++ -g -o main main.cpp Binomial-Heap.o fibonacci.o van_emde.o node.o
