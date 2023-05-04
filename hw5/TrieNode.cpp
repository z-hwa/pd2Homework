#include"Trie.h"
#include<string>
#include<cstring>
using namespace std;

//建構子
TrieNode::TrieNode() {
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) next[i] = NULL; //初始化子節點的位置
	isWord = false; //節點預設=不是單字
}

//解構子
TrieNode::~TrieNode() {
	//循環當前節點的 所有子節點
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) {
		if (next[i]) delete next[i]; //如果不是NULL 刪除
	}
}

//將當前節點 標記為一個單字
void TrieNode::SetIsWord() {
	this->isWord = true;
}

bool TrieNode::CheckIsWord() {
	return this->isWord;
}