#variable
CC = g++
CFLAGS = -Wall -g

#target
all: hw1.o
	$(CC) $(CFLAGS) -o hw1 hw1.o
hw1.o: hw1.cpp
	$(CC) $(CFLAGS) -c hw1.cpp

#clean
clean:
	rm -rf *.o
