CC=g++

TestDijkstras: node.o Binomial-Heap.o TestDijkstras.cpp
	g++ -g -o TestDijkstras TestDijkstras.cpp Binomial-Heap.o node.o