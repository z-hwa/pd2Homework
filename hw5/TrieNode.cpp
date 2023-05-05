#include"Trie.h"
#include<string>
#include<cstring>
using namespace std;

//�غc�l
TrieNode::TrieNode() {
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) next[i] = NULL; //��l�Ƥl�`�I����m
	isWord = false; //�`�I�w�]=���O��r
}

//�Ѻc�l
TrieNode::~TrieNode() {
	//�`����e�`�I�� �Ҧ��l�`�I
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) {
		if (next[i]) delete next[i]; //�p�G���ONULL �R��
	}
}

//�N��e�`�I �аO���@�ӳ�r
void TrieNode::SetIsWord(string textId) {
	this->isWord = true;

	//�o�{�ӳ�r �w�g���F�ۦP���ӷ��奻 ���+1
	if (this->recordIds.count(textId) == 1) this->recordIds[textId] += 1;
	else this->recordIds[textId] = 1; //�S���N�Ы� �ó]��1
}

//�ˬd��Ӹ`�I�O�_�w�g�Φ���r
bool TrieNode::CheckIsWord() {
	return this->isWord;
}