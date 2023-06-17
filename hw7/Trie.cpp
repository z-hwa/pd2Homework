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
void Trie::Insert(const string word, const string textId) {
	TrieNode* p = root; //設置用以讀取的指針
						//default root

	int index = -1; //用於標記 字元編碼後的index
					//Ex. a->0

	//尋訪樹中符合的前綴
	for (int i = 0; i < (int)word.size(); i++) {
		char wordLower = tolower(word[i]); //字元轉小寫
		index = wordLower - 'a'; //編碼當前字元為index

		//如果找不到，就插入新的節點 (編碼規則: 當前字元減去'a'作為index)
		if (p->next[index] == NULL) {
			p->next[index] = new TrieNode();
		}

		//移動讀取的指針p
		p = p->next[index];
	}

	//完成尋訪後 代表成功將當前單字插入樹中 並將這個節點 標記為一個單字
	p->SetIsWord(textId); //設為單字 並設定該單字的文本id
}

//檢查單字是否正確找到
bool Trie::IsWantedWord(const TrieNode* wordNode) {
	//如果是空指針: false
	//checkisword 回傳 false: false
	if (wordNode == NULL || !wordNode->CheckIsWord()) return false;
	else return true;
}

//尋訪樹
TrieNode* Trie::Searching(const string word) {
	TrieNode* p = root; //設定讀取的指針 root
	int index = -1; //紀錄編碼後的字元index

	//條件:p不為NULL 且 當前未超過查找單字字元數量
	for (int i = 0; i < (int)word.size() && p; i++) {
		char wordLower = tolower(word[i]); //轉成小寫
		
		index = wordLower - 'a'; //編碼當前字元 為 index
		p = p->next[index]; //前往下一個節點
	}

	return p; //p 不是空指針
			  //p.isword 是對的
			  //才確定找到單字
}

//回傳文本來源
unordered_map<string, int> Trie::GetSourceMap(const TrieNode* wordNode) {
	return wordNode->recordIds;
}