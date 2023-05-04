#variable
CC = g++
CFLAGS = -Wall -g -std=c++17

#target
all: main.o TrieNode.o Trie.o
	$(CC) $(CFLAGS) -o hw5 main.o TrieNode.o Trie.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

TrieNode.o: TrieNode.cpp
	$(CC) $(CFLAGS) -c TrieNode.cpp

Trie.o: Trie.cpp
	$(CC) $(CFLAGS) -c Trie.cpp


#clean
clean:
	rm -rf *.o