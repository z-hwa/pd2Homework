#ifndef _TRIE_H
#define _TRIE_H
#include<iostream>
using namespace std;

class TrieNode {
public:
	//建構子
	TrieNode() {
		memset(next, NULL, sizeof(next)); //初始化子節點的位置
		isWord = false; //節點預設=不是單字
	}

	//解構
	~TrieNode() {
		//循環當前節點的 所有子節點
		for (int i = 0; i < LITTEL_LETTER_NUM; i++) {
			if (next(i)) delete next[i]; //如果不是NULL 刪除
		}
	}
private:
	static const int LITTLE_LETTER_NUM = 26; //小寫字母數量
	TrieNode* next[LITTER_LETTER_NUM]; //當前節點的子節點位置 26個字母
	
	bool isWord; //目前節點是不是一個單字
};

#endif