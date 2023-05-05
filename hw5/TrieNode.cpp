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
void TrieNode::SetIsWord(string textId) {
	this->isWord = true;

	//發現該單字 已經有了相同的來源文本 原值+1
	if (this->recordIds.count(textId) == 1) this->recordIds[textId] += 1;
	else this->recordIds[textId] = 1; //沒有就創建 並設為1
}

//檢查到該節點是否已經形成單字
bool TrieNode::CheckIsWord() {
	return this->isWord;
}