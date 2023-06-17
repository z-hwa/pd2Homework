#variable
CC = g++
CFLAGS = -Wall -g -std=c++17

#target
all: main.o TrieNode.o Trie.o WordsData.o
	$(CC) $(CFLAGS) -o hw7 main.o TrieNode.o Trie.o WordsData.o

main.o: main.cpp Trie.h
	$(CC) $(CFLAGS) -c main.cpp

TrieNode.o: TrieNode.cpp Trie.h
	$(CC) $(CFLAGS) -c TrieNode.cpp

Trie.o: Trie.cpp Trie.h
	$(CC) $(CFLAGS) -c Trie.cpp

WordsData.o: WordsData.cpp WordsData.h
	$(CC) $(CFLAGS) -c WordsData.cpp


#clean
clean:
	rm -rf *.o