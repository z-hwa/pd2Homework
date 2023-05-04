#include"Trie.h"
#include<string>
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
void Trie::Insert(string word) {
	TrieNode* p = root; //�]�m�ΥHŪ�������w�A�qroot�}�l
	int index = -1; //�Ω�аOindex

	//�M�X�𤤲ŦX���e��
	for (int i = 0; i < (int)word.size(); i++) {
		index = word[i] - 'a'; //�ഫ��e�d��r�� �� index

		//�p�G�䤣��A�N���J�s���`�I (��e�r����h'a'�@��index)
		if (p->next[index] == NULL) {
			p->next[index] = new TrieNode();
		}

		//����Ū�������wp
		p = p->next[index];
	}

	//�����M�X�� �N���\�N��e��r���J�� �ñN�o�Ӹ`�I �аO���@�ӳ�r
	p->SetIsWord(); //�]����r
}

bool Trie::Searching(string word) {
	TrieNode* p = root; //�]�wŪ�������w root
	int index;

	//����:p������ �B ��e���W�L�d���r�r���ƶq
	for (int i = 0; i < (int)word.size() && p; i++) {
		index = word[i] - 'a'; //�ഫ��e�d��r�� �� index
		p = p->next[index]; //�e���U�@�Ӹ`�I
	}

	//�p�Gp������ �B �Ӹ`�I�O��r �^�� true
	return p && p->CheckIsWord();
}