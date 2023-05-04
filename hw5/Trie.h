#ifndef _TRIE_H
#define _TRIE_H
#include<iostream>
using namespace std;

class TrieNode {
public:
	//�غc�l
	TrieNode() {
		memset(next, NULL, sizeof(next)); //��l�Ƥl�`�I����m
		isWord = false; //�`�I�w�]=���O��r
	}

	//�Ѻc
	~TrieNode() {
		//�`����e�`�I�� �Ҧ��l�`�I
		for (int i = 0; i < LITTEL_LETTER_NUM; i++) {
			if (next(i)) delete next[i]; //�p�G���ONULL �R��
		}
	}
private:
	static const int LITTLE_LETTER_NUM = 26; //�p�g�r���ƶq
	TrieNode* next[LITTER_LETTER_NUM]; //��e�`�I���l�`�I��m 26�Ӧr��
	
	bool isWord; //�ثe�`�I�O���O�@�ӳ�r
};

#endif