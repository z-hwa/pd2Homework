#include<iostream>
#include"Trie.h"
using namespace std;

Trie* tree = new Trie();

int main() {

	tree->Insert("apple");
	cout << tree->Searching("appe");

	return 0;
}