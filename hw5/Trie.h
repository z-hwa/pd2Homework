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

	void SetIsWord(string textId); //設定節點(自己)為一個單字
	bool CheckIsWord(); //確認是不是單字

	friend class Trie; //將樹本體視為朋友

private:
	static const int LITTLE_LETTER_NUM = 26; //小寫字母數量
	TrieNode* next[LITTLE_LETTER_NUM]; //當前節點的子節點位置 26個字母

	bool isWord; //目前節點是不是一個單字
	unordered_map<string, int>  recordIds; //紀錄包含該單字的文本id
};

//trie樹本體
class Trie {
public:

	Trie(); //建構子
	~Trie(); //解構子

	void Insert(string word, string textId); //在樹中插入單字
	unordered_map<string, int> GetSourceMap(TrieNode* wordNode); //根據單字節點 取得map
	TrieNode* Searching(string word); //回傳根據單字 找尋到的最終節點
	bool IsWantedWord(TrieNode* wordNode); //根據傳入節點 判斷是否為我們一個單字
private:
	TrieNode* root; //根節點
};
#endif