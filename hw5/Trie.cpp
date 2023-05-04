#include"Trie.h"
#include<string>
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
void Trie::Insert(string word) {
	TrieNode* p = root; //設置用以讀取的指針，從root開始
	int index = -1; //用於標記index

	//尋訪樹中符合的前綴
	for (int i = 0; i < (int)word.size(); i++) {
		index = word[i] - 'a'; //轉換當前查找字元 為 index

		//如果找不到，就插入新的節點 (當前字元減去'a'作為index)
		if (p->next[index] == NULL) {
			p->next[index] = new TrieNode();
		}

		//移動讀取的指針p
		p = p->next[index];
	}

	//完成尋訪後 代表成功將當前單字插入樹中 並將這個節點 標記為一個單字
	p->SetIsWord(); //設為單字
}

bool Trie::Searching(string word) {
	TrieNode* p = root; //設定讀取的指針 root
	int index;

	//條件:p不為空 且 當前未超過查找單字字元數量
	for (int i = 0; i < (int)word.size() && p; i++) {
		index = word[i] - 'a'; //轉換當前查找字元 為 index
		p = p->next[index]; //前往下一個節點
	}

	//如果p不為空 且 該節點是單字 回傳 true
	return p && p->CheckIsWord();
}