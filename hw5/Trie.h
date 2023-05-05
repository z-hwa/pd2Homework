#ifndef _TRIE_H
#define _TRIE_H
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

//trie�𪺸`�I
class TrieNode {
public:
	TrieNode(); //�غc�l
	~TrieNode(); //�Ѻc�l

	void SetIsWord(string textId); //�]�w�`�I(�ۤv)���@�ӳ�r
	bool CheckIsWord(); //�T�{�O���O��r

	friend class Trie; //�N��������B��

private:
	static const int LITTLE_LETTER_NUM = 26; //�p�g�r���ƶq
	TrieNode* next[LITTLE_LETTER_NUM]; //��e�`�I���l�`�I��m 26�Ӧr��

	bool isWord; //�ثe�`�I�O���O�@�ӳ�r
	unordered_map<string, int>  recordIds; //�����]�t�ӳ�r���奻id
};

//trie����
class Trie {
public:

	Trie(); //�غc�l
	~Trie(); //�Ѻc�l

	void Insert(string word, string textId); //�b�𤤴��J��r
	unordered_map<string, int> GetSourceMap(TrieNode* wordNode); //�ھڳ�r�`�I ���omap
	TrieNode* Searching(string word); //�^�Ǯھڳ�r ��M�쪺�̲׸`�I
	bool IsWantedWord(TrieNode* wordNode); //�ھڶǤJ�`�I �P�_�O�_���ڭ̤@�ӳ�r
private:
	TrieNode* root; //�ڸ`�I
};
#endif