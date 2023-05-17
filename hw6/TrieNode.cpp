#include"Trie.h"
#include<string>
#include<cstring>
#include<cmath>
using namespace std;

//�غc�l
TrieNode::TrieNode() {
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) next[i] = NULL; //��l�� ���`�I���l�`�I��m��NULL
	isWord = false; //default ���O��r
}

//�Ѻc�l
TrieNode::~TrieNode() {
	//�`�����`�I���l�`�I
	for (int i = 0; i < LITTLE_LETTER_NUM; i++) {
		if (next[i]) delete next[i]; //�p�G���ONULL �R��
	}
}

//�N��e�`�I �аO����r
void TrieNode::SetIsWord(const string textId) {
	this->isWord = true; //�аO���`�I����r

	if (this->recordIds.count(textId) == 1) {
		this->recordIds[textId] += 1; //�o�{����r �s�b�ۦP�奻��id ���+1
									  //�����b�P�@�Ӥ奻�� �X�{�h���ӳ�r
	}
	else this->recordIds[textId] = 1; //����r ���s�b�o���إߪ��奻id
									  //set 1 
}

//�ˬd���`�I�O�_����r
bool TrieNode::CheckIsWord() const {
	return this->isWord;
}

//�p���e��IDF
void TrieNode::CountIDF(const double totalTextNum) {
	double appearTimes = this->recordIds.size(); //�����e��r �s�b��h�ּƶq���奻��

	this->idf = log10(totalTextNum/appearTimes); //�p���e��idf
												 //set idf
}

double TrieNode::GetIDF() {
	return this->idf;
}