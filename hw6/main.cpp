#include<iostream>
#include"Trie.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<utility>
using namespace std;

const int needFileNum = 3; //�ݭn���ɮ׼ƶq
Trie* trie = new Trie(); //�j�M����������
fstream file; //�Ω�s���ɮת��y

double totalTextNum = 0; //�Ҧ��奻�ƶq
int kNum = 0; //�d�ߵ��G��X�ƶq

bool ArgcIsWrong(int argc, char** argv);
bool OpenFile(string path);

void TextToTrie(string id, string text);
vector<string> SpiltText(string text);
bool IsAlpha(char c);
void ProductTrie();

//void FulllyMapSearch();
void PartMapSearch();

//bool Comp(string id1, string id2);
bool Comp(pair<string, double> text1, pair<string, double> text2);

int main(int argc, char** argv) {

    if (ArgcIsWrong(argc, argv) == true) return 1; //�ˬd��J���ƶq(3)
    kNum = stoi(argv[3]); //set �d�ߵ��G��X�ƶq

    if (OpenFile(argv[1]) == false) return 1; //�}��corpus �ýT�{�O�_���T���}

    ProductTrie(); //�Hcorpus��� ����trie
    if (OpenFile(argv[2]) == false) return 1; //�}��query

    PartMapSearch();

	return 0;
}

//�����ǰt�d��(���IDF�H��kNum)
void PartMapSearch() {
    string text; //�x�s�C�@�檺�奻
    TrieNode* p; //�Ω�s���`�I�����w

    unordered_map<string, double> totalMap; //�[�`�X�{���奻 IDF�`�M
    unordered_map<string, int> tempMap; //�������V�S�w����r��map��ref

    vector<pair<string, double>> sortingText; //�Ω�Ƨ�text

    //�q�ɮ׬y���X��� �H �� ���B�z��� 
    while (getline(file, text))
    {
        totalMap.clear(); //��s������ ��s�p��IDF��map
        sortingText.clear(); //�M�űƧ�vector

        vector<string> words; //�x�s��r
        words = SpiltText(text); //���γ�r

        //�d������r
        for (auto it = words.begin(); it != words.end(); it++) {
            tempMap.clear();
            string word = *it; //��o��r

            p = trie->Searching(word); //��o�j�M���G���w

            //�p�G���T���
            if (trie->IsWantedWord(p) == true) {
                p->CountIDF(totalTextNum); //�p�⦹����r���̲�idf
                tempMap = trie->GetSourceMap(p); //��o����r��ref of map

                for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                    string key = (*it).first; //���o�� (id)

                    //.count�^��1 �N���� �ҥH+idf
                    if (totalMap.count(key) == 1) totalMap[key] += p->GetIDF(); 
                    else totalMap[key] = p->GetIDF();
                }
            }
        }

        //total map �ಾ�� �Ƨ�vecter
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            pair<string, double> eachText;
            eachText.first = (*it).first, eachText.second = (*it).second;
            sortingText.push_back(eachText);
        }

        //�Ƨ�id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //�p�G�S�����
        if (sortingText.size() == 0) cout << "�S������奻�ǰt���@����r";
        else {
            int outNum = 0; //�����w�g��X���ƶq
            
            //��Xid����ŦXknum �άO ���s�b�ǰt��>0���奻
            for (auto it = sortingText.begin(); it != sortingText.end() && outNum < kNum; it++, outNum++) {
                cout << (*it).first;
#ifdef IDF
                cout << ":" << (*it).second;
#endif // IDF

                if (it + 1 != sortingText.end() && outNum != kNum) cout << " "; //�U�@��
                                                                                    //���O�ǰt��>0��vec end pointer
                                                                                    //�H��knum�̫�@��
                                                                                    //��X�ť�
            }
        }

        cout << endl; //����
    }

    return;
}

//������ (id descending order)
/*bool Comp(string id1, string id2) {
    return stoi(id1) <= stoi(id2);
}
*/
bool Comp(pair<string, double> text1, pair<string, double> text2) {
    if (text1.second != text2.second) return text1.second > text2.second;
    else return stoi(text1.first) < stoi(text2.first);
}

//�����ǰt�d��
/*
void FulllyMapSearch() {
    string text; //�x�s�C�@�檺�奻
    TrieNode* p; //�Ω�s���`�I�����w
    
    unordered_map<string, int> totalMap; //�[�`�X�{���奻 �ŦX������r����
    unordered_map<string, int> tempMap; //�������V�S�w����r��map��ref
    
    vector<string> sortingText; //�Ω�Ƨ�text

    //�q�ɮ׬y���X��� �H �� ���B�z��� 
    while (getline(file, text))
    {
        totalMap.clear(); //��s������ ��s�p��ƶq��map
        sortingText.clear(); //�M��

        vector<string> words; //�x�s��r
        words = SpiltText(text); //���γ�r
    
        //�d������r
        for (auto it = words.begin(); it != words.end(); it++) {
            tempMap.clear();
            string word = *it; //��o��r
            
            p = trie->Searching(word); //��o�j�M���G���w

            //�p�G���T���
            if (trie->IsWantedWord(p) == true) {
                tempMap = trie->GetSourceMap(p);

                for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                    string key = (*it).first; //���o��
                    //int values = (*it).second; //���o��

                    //.count�^��1 �N���� �ҥH+1 �]���O�ˬdkey���奻�s���s�b��e����r
                    if (totalMap.count(key) == 1) totalMap[key] += 1;
                    else totalMap[key] = 1;
                }
            }
        }

        int keyWordNum = words.size(); //��o����r�ƶq
        
        //�d��total map�ƶq�ŦX �N��i�Ƨ�vec��
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            string key = (*it).first; //��okey (text id)
            //cout << key << ":" << totalMap[key] << endl;
            if (totalMap[key] == keyWordNum) {
                sortingText.push_back(key);
            }
        }

        //�Ƨ�id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //�p�G�S�����
        if (sortingText.size() == 0) cout << -1;
        else {
            //��X��쪺id
            for (auto it = sortingText.begin(); it != sortingText.end(); it++) {
                cout << (*it);
                if (it + 1 != sortingText.end()) cout << " ";
            }
        }

        cout << endl; //����
    }

    return ;
}
*/

void ProductTrie() {
    string text; //�x�s�C�@�檺�奻

    //�q�ɮ׬y���X��� 
    while (getline(file, text))
    {
        size_t pos = text.find(','); //���Ĥ@��','����m
        string id = text.substr(0, pos); //���Xid

        TextToTrie(id, text); //��K�[��e�奻
        totalTextNum += 1; //�奻�ƶq+1
    }
    
    return ;
}

//�˴��r���O���O �r��
//�p�G�O ' ' �O�d
bool IsAlpha(char c) {
    if (c == ' ') return false;
    else return !isalpha(c); //�p�G�O�r�� �^��false
                             //other true
}

//���Τ奻
vector<string> SpiltText(string text) {
    vector<string> words; //�Ω��x�s���Ϋ᪺�C�ӳ�r

    text.erase(remove_if(text.begin(), text.end(), IsAlpha), text.end()); //��D�r�����r�� �����R��
    
    stringstream ss(text); //�N�奻��i �r��y
    string token; //�Ȧs��r

    //�p�G�i�H�q�r��y�����X�F��
    while (ss >> token) {
        words.push_back(token); //�N���X����r��iwords
    }

    return words;
}

//�N�Ҧ��奻���X�{����r ���J��
void TextToTrie(string id, string text) {
    vector<string> words = SpiltText(text); //���� ���Τ奻 �^�Ǫ���rvector

    //�M�X�Ҧ�����r �ä@�@�N�䴡�J���
    for (auto it = words.begin(); it != words.end(); it++) {
        string word = *it; //��o�ӫ��Ы��V���� �]�N�O��r
        trie->Insert(word, id); //�b�ثe�o�ʾ� ���J��r �ðO���ӷ�id
    }
}

//���}�ɮ�
bool OpenFile(string path) {
    file.close();
    file.open(path, ios::in);
    if (!file.is_open()) {
        cout << "file open failure: " << path << endl;
        return false; //�ɮרS�����T���}
    }
    return true;
}

//�ˬd��J�ɮ׼ƶq
bool ArgcIsWrong(int argc, char** argv) {
    //�T�{��J�ѼƼƶq�O�_���T�]3�^ 
    if (argc == needFileNum + 1) {
        return false;
    }
    else {
        cout << "Usage: " << argv[0] << "file_path" << endl;
        return true;
    }
}