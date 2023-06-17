#include"Trie.h"
#include<string>
#include<unordered_map>
using namespace std;

//�غc�l
Trie::Trie() {
	root = new TrieNode(); //�]�m�ڸ`�I
}

//�Ѻc�l
Trie::~Trie() {
	delete root; //�R���ڸ`�I
}

//�b�𤤴��J��r
void Trie::Insert(const string word, const string textId) {
	TrieNode* p = root; //�]�m�ΥHŪ�������w
						//default root

	int index = -1; //�Ω�аO �r���s�X�᪺index
					//Ex. a->0

	//�M�X�𤤲ŦX���e��
	for (int i = 0; i < (int)word.size(); i++) {
		char wordLower = tolower(word[i]); //�r����p�g
		index = wordLower - 'a'; //�s�X��e�r����index

		//�p�G�䤣��A�N���J�s���`�I (�s�X�W�h: ��e�r����h'a'�@��index)
		if (p->next[index] == NULL) {
			p->next[index] = new TrieNode();
		}

		//����Ū�������wp
		p = p->next[index];
	}

	//�����M�X�� �N���\�N��e��r���J�� �ñN�o�Ӹ`�I �аO���@�ӳ�r
	p->SetIsWord(textId); //�]����r �ó]�w�ӳ�r���奻id
}

//�ˬd��r�O�_���T���
bool Trie::IsWantedWord(const TrieNode* wordNode) {
	//�p�G�O�ū��w: false
	//checkisword �^�� false: false
	if (wordNode == NULL || !wordNode->CheckIsWord()) return false;
	else return true;
}

//�M�X��
TrieNode* Trie::Searching(const string word) {
	TrieNode* p = root; //�]�wŪ�������w root
	int index = -1; //�����s�X�᪺�r��index

	//����:p����NULL �B ��e���W�L�d���r�r���ƶq
	for (int i = 0; i < (int)word.size() && p; i++) {
		char wordLower = tolower(word[i]); //�ন�p�g
		
		index = wordLower - 'a'; //�s�X��e�r�� �� index
		p = p->next[index]; //�e���U�@�Ӹ`�I
	}

	return p; //p ���O�ū��w
			  //p.isword �O�諸
			  //�~�T�w����r
}

//�^�Ǥ奻�ӷ�
unordered_map<string, int> Trie::GetSourceMap(const TrieNode* wordNode) {
	return wordNode->recordIds;
}