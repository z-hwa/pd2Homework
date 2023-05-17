#variable
CC = g++
CFLAGS = -Wall -g -std=c++17

#target
all: main.o TrieNode.o Trie.o
	$(CC) $(CFLAGS) -o hw6 main.o TrieNode.o Trie.o

main.o: main.cpp Trie.h
	$(CC) $(CFLAGS) -c main.cpp

TrieNode.o: TrieNode.cpp Trie.h
	$(CC) $(CFLAGS) -c TrieNode.cpp

Trie.o: Trie.cpp Trie.h
	$(CC) $(CFLAGS) -c Trie.cpp


#clean
clean:
	rm -rf *.o