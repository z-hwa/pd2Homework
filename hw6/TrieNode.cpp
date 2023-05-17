#include"Trie.h"
#include<string>
#include<cstring>
#include<cmath>
using namespace std;

//建構子
TrieNode::TrieNode() {
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) next[i] = NULL; //初始化 此節點的子節點位置為NULL
	isWord = false; //default 不是單字
}

//解構子
TrieNode::~TrieNode() {
	//循環此節點的子節點
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) {
		if (next[i]) delete next[i]; //如果不是NULL 刪除
	}
}

//將當前節點 標記為單字
void TrieNode::SetIsWord(const string textId) {
	this->isWord = true; //標記此節點為單字

	if (this->recordIds.count(textId) == 1) {
		this->recordIds[textId] += 1; //發現此單字 存在相同文本的id 原值+1
									  //說明在同一個文本中 出現多次該單字
	}
	else this->recordIds[textId] = 1; //此單字 不存在這次建立的文本id
									  //set 1 
}

//檢查此節點是否為單字
bool TrieNode::CheckIsWord() const {
	return this->isWord;
}

//計算當前的IDF
void TrieNode::CountIDF(const double totalTextNum) {
	double appearTimes = this->recordIds.size(); //獲取當前單字 存在於多少數量的文本中

	this->idf = log10(totalTextNum/appearTimes); //計算當前的idf
												 //set idf
}

double TrieNode::GetIDF() {
	return this->idf;
}