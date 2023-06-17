#ifndef _TRIE_H
#define _TRIE_H
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

//trie樹的節點
class TrieNode {
public:
	TrieNode(); //建構子
	~TrieNode(); //解構子

	void SetIsWord(const string textId); //設定自己為單字
	bool CheckIsWord() const; //檢查是否為單字
	void CountIDF(const double totalTextNum); //計算當前的IDF
	double GetIDF(); //獲得此節點的idf

	friend class Trie; //將trie class視為朋友

private:
	static const int LITTLE_LETTER_NUM = 26; //小寫字母數量
	TrieNode* next[LITTLE_LETTER_NUM]; //儲存此節點的子節點位置，代表26個字母

	bool isWord; //此節點是否為單字
	double idf; //紀錄單字的idf值
	unordered_map<string, int>  recordIds; //紀錄包含該單字的文本id
										   //Ex. 145544:10
										   //代表在id為145544的文本中，出現這個單字10次
};

//trie樹本體
class Trie {
public:

	Trie(); //建構子
	~Trie(); //解構子

	void Insert(const string word,const string textId); //在樹中插入單字
	unordered_map<string, int> GetSourceMap(const TrieNode* wordNode); //根據單字節點指針 取得包含該單字的文本id (map)
	TrieNode* Searching(const string word); //回傳根據單字 尋訪的最終指針
	bool IsWantedWord(const TrieNode* wordNode); //根據傳入指針 判斷是否為單字
private:
	TrieNode* root; //根節點
};
#endif