#variable
CC = g++
CFLAGS = -Wall -g

#target
all: main.o employeeClass.o
	$(CC) $(CFLAGS) -o hw3 main.o employeeClass.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 
employeeClass.o: employeeClass.cpp
	$(CC) $(CFLAGS) -c employeeClass.cpp 

#clean
clean:
	rm -rf *.o
