#variable
CC = g++
CFLAGS = -Wall -g

#target
all: sortByAttr.o
	$(CC) $(CFLAGS) -o hw2 sortByAttr.o
sortByAttr.o: sortByAttr.cpp
	$(CC) $(CFLAGS) -c sortByAttr.cpp 

#clean
clean:
	rm -rf *.o
