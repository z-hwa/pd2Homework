#include<iostream>
#include"Trie.h"
#include"WordsData.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;

const double eps = 1e-8; //epsilon
const int needFileNum = 3; //�ݭn���ɮ׼ƶq
Trie* trie = new Trie(); //�j�M����������
fstream file; //�Ω�s���ɮת��y

double totalTextNum = 0; //�Ҧ��奻�ƶq
int kNum = 0; //�d�ߵ��G��X�ƶq

unordered_map<string, int> wordTotalNum; //�����@�Ӥ奻�����`��r��

//declare
bool ArgcIsWrong(int argc, char** argv);
bool OpenFile(string path);

void TextToTrie(string id, string text);
vector<string> SpiltText(string text);
bool IsAlpha(char c);
void ProductTrie();
//

//void FulllyMapSearch();
void PartMapSearch();

//bool Comp(string id1, string id2);
bool Comp(pair<string, double> text1, pair<string, double> text2);

//�������r���(idf, new_tf)
bool Comp2(Keywords, Keywords);

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

    unordered_map<string, vector<Keywords>> totalMap; //�[�`�X�{���奻 �d��쪺�Ҧ�����r���
    unordered_map<string, int> tempMap; //�������V�S�w����r��map��ref

    vector<pair<string, double>> sortingText; //�Ω�Ƨ�text

    //�q�ɮ׬y���X��� �H �� ���B�z��� 
    while (getline(file, text))
    {
        totalMap.clear(); //��s������ ��s�p��IDF��map
        sortingText.clear(); //�M�űƧ�vector
        Keywords* k = new Keywords(); //�Ȧsk

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

#ifdef DEBUG
                cout << word << ": " << p->GetIDF() << endl;
#endif

                //�B������r��idf������0
                if (p->GetIDF() != 0) {
                    tempMap = trie->GetSourceMap(p); //��o����r��ref of map

                    for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                        //cout << "timesssss" << endl;
                        string key = (*it).first; //���o�� (�奻id)
                        int occurence = (*it).second; //���o������r�b�奻�����X�{����
                        
                        double idf = p->GetIDF(); //���oidf
                        //cout << key << ": " << idf << endl;
                        //cout << key << endl;
                        //cout << wordTotalNum[key] << endl; //test
                        double new_tf = occurence / wordTotalNum[key]; //���otf
                        //cout << "true" << endl;

                        k->SetValue(idf, new_tf); //�ͦ��s������r���

                        totalMap[key].push_back(*k); //��ivector��
                        //cout << "test1" << endl;
                    }
                    //cout << "test a" << endl;
                }
            }

            //cout << "testp" << endl;
        }

        //�ƧǨC�Ӥ奻������r���
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            sort((*it).second.begin(), (*it).second.end(), Comp2); //�Ƨ�idf, new_tf

            int recTimes = 0; //�w�[�`������r�ƶq
            double r; //r value

            cout << "S_ID_" << (*it).first << ": ";

            for (auto p = (*it).second.begin(); p != (*it).second.end()/* && recTimes < 3*/; p++, recTimes++) {
                r += (*p).getIdf() * (*p).getNew_tf(); //�֥[r��
                cout << (*p).getIdf() << ", " << (*p).getNew_tf();
            }

            cout << endl;

            pair<string, double> eachText;
            eachText.first = (*it).first, eachText.second = r;
            sortingText.push_back(eachText);
        }

        //�Ƨ�id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //�ھ�knum��X
        auto it = sortingText.begin(); //���V�奻�����w
        int legalNum = sortingText.size(); //�ŦX�ǰt���奻�ƶq
        for (int i = 0; i < kNum; i++) {
            //�p�G��X���ƶq �֩󦨥\�ǰt���奻�ƶq ��Xid it++
            if (i < legalNum) {
                cout << (*it).first << ": " << (*it).second;
                it++;
            }
            else cout << "-1"; //���s�b�h��X-1

            if (i != kNum - 1) cout << " "; //�U�@��
                                                                       //���O�ǰt��>0��vec end pointer
                                                                       //�H��knum - 1��
                                                                       //��X�ť�
        }

        cout << endl; //����
    }

    return;
}

bool Comp(pair<string, double> text1, pair<string, double> text2) {
    if (text1.second != text2.second) return text1.second > text2.second;
    else return stoi(text1.first) < stoi(text2.first);
}

//�������r���(idf, tf)
bool Comp2(Keywords word1, Keywords word2) {
    double idf1 = word1.getIdf(), idf2 = word2.getIdf();
    double tf1 = word1.getNew_tf(), tf2 = word2.getNew_tf();

    
    //�B�I�Ƥ��۵�����
    if (fabs(idf1 - idf2) > eps) return idf1 > idf2;
    else return (idf1 * tf1) > (idf2 * tf2);
}

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
    wordTotalNum[id] = words.size(); //�����C�Ӥ奻���`��r��

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