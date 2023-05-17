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

	void SetIsWord(const string textId); //�]�w�ۤv����r
	bool CheckIsWord() const; //�ˬd�O�_����r
	void CountIDF(const double totalTextNum); //�p���e��IDF
	double GetIDF(); //��o���`�I��idf

	friend class Trie; //�Ntrie class�����B��

private:
	static const int LITTLE_LETTER_NUM = 26; //�p�g�r���ƶq
	TrieNode* next[LITTLE_LETTER_NUM]; //�x�s���`�I���l�`�I��m�A�N��26�Ӧr��

	bool isWord; //���`�I�O�_����r
	double idf; //������r��idf��
	unordered_map<string, int>  recordIds; //�����]�t�ӳ�r���奻id
										   //Ex. 145544:10
										   //�N��bid��145544���奻���A�X�{�o�ӳ�r10��
};

//trie����
class Trie {
public:

	Trie(); //�غc�l
	~Trie(); //�Ѻc�l

	void Insert(const string word,const string textId); //�b�𤤴��J��r
	unordered_map<string, int> GetSourceMap(const TrieNode* wordNode); //�ھڳ�r�`�I���w ���o�]�t�ӳ�r���奻id (map)
	TrieNode* Searching(const string word); //�^�Ǯھڳ�r �M�X���̲׫��w
	bool IsWantedWord(const TrieNode* wordNode); //�ھڶǤJ���w �P�_�O�_����r
private:
	TrieNode* root; //�ڸ`�I
};
#endif