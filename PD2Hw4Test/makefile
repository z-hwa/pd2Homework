CC = g++
CFLAGS = -g -Wall -std=c++17

all: main.o EmployeeClass.o
	$(CC) $(CFLAGS) -o testDataProducter main.o EmployeeClass.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
EmployeeClass.o: EmployeeClass.cpp
	$(CC) $(CFLAGS) -c EmployeeClass.cpp

clean: 
	rm -rf *.o
