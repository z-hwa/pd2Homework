#include"Trie.h"
#include<string>
#include<unordered_map>
using namespace std;

//建構子
Trie::Trie() {
	root = new TrieNode(); //設置根節點
}

//解構子
Trie::~Trie() {
	delete root; //刪除根節點
}

//在樹中插入單字
void Trie::Insert(string word, string textId) {
	TrieNode* p = root; //設置用以讀取的指針，從root開始
	int index = -1; //用於標記index

	//尋訪樹中符合的前綴
	for (int i = 0; i < (int)word.size(); i++) {
		char wordLower = tolower(word[i]);
		index = wordLower - 'a'; //轉換當前查找字元 為 index

		//如果找不到，就插入新的節點 (當前字元減去'a'作為index)
		if (p->next[index] == NULL) {
			p->next[index] = new TrieNode();
		}

		//移動讀取的指針p
		p = p->next[index];
	}

	//完成尋訪後 代表成功將當前單字插入樹中 並將這個節點 標記為一個單字
	p->SetIsWord(textId); //設為單字 並設定該單字的文本id
}

//檢查單字是不是正確找到
bool Trie::IsWantedWord(TrieNode* wordNode) {
	//如果是空指針: false
	//checkisword 回傳 false: false
	if (wordNode == NULL || !wordNode->CheckIsWord()) return false;
	else return true;
}

//尋訪樹
TrieNode* Trie::Searching(string word) {
	TrieNode* p = root; //設定讀取的指針 root
	int index;

	//條件:p不為空 且 當前未超過查找單字字元數量
	for (int i = 0; i < (int)word.size() && p; i++) {
		char wordLower = tolower(word[i]); //轉成小寫
		
		index = wordLower - 'a'; //轉換當前查找字元 為 index
		p = p->next[index]; //前往下一個節點
	}

	return p; //p 不是空指針
			  //p.isword 是對的
			  //才確定找到單字
}

//回傳文本來源
unordered_map<string, int> Trie::GetSourceMap(TrieNode* wordNode) {
	return wordNode->recordIds;
}