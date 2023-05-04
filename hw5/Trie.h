#ifndef _TRIE_H
#define _TRIE_H
#include<iostream>
#include<string>
using namespace std;

//trie�𪺸`�I
class TrieNode {
public:
	TrieNode(); //�غc�l
	~TrieNode(); //�Ѻc�l

	void SetIsWord(); //�]�w�`�I(�ۤv)���@�ӳ�r
	bool CheckIsWord(); //�T�{�O���O��r

	friend class Trie; //�N��������B��

private:
	static const int LITTLE_LETTER_NUM = 26; //�p�g�r���ƶq
	TrieNode* next[LITTLE_LETTER_NUM]; //��e�`�I���l�`�I��m 26�Ӧr��

	bool isWord; //�ثe�`�I�O���O�@�ӳ�r
};

//trie����
class Trie {
public:

	Trie(); //�غc�l
	~Trie(); //�Ѻc�l

	void Insert(string word); //�b�𤤴��J��r
	bool Searching(string word); //��M��r
private:
	TrieNode* root; //�ڸ`�I
};
#endif