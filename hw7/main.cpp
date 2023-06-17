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
const int needFileNum = 3; //需要的檔案數量
Trie* trie = new Trie(); //搜尋引擎的樹本體
fstream file; //用於存取檔案的流

double totalTextNum = 0; //所有文本數量
int kNum = 0; //查詢結果輸出數量

unordered_map<string, int> wordTotalNum; //紀錄一個文本內的總單字數

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

//比較關鍵字資料(idf, new_tf)
bool Comp2(Keywords, Keywords);

int main(int argc, char** argv) {

    if (ArgcIsWrong(argc, argv) == true) return 1; //檢查輸入的數量(3)
    kNum = stoi(argv[3]); //set 查詢結果輸出數量

    if (OpenFile(argv[1]) == false) return 1; //開啟corpus 並確認是否正確打開

    ProductTrie(); //以corpus資料 產生trie
    if (OpenFile(argv[2]) == false) return 1; //開啟query

    PartMapSearch();

	return 0;
}

//部分匹配查詢(基於IDF以及kNum)
void PartMapSearch() {
    string text; //儲存每一行的文本
    TrieNode* p; //用於存取節點的指針

    unordered_map<string, vector<Keywords>> totalMap; //加總出現的文本 查找到的所有關鍵字資料
    unordered_map<string, int> tempMap; //紀錄指向特定關鍵字的map的ref

    vector<pair<string, double>> sortingText; //用於排序text

    //從檔案流取出資料 以 行 為處理單位 
    while (getline(file, text))
    {
        totalMap.clear(); //對新的提問 更新計算IDF的map
        sortingText.clear(); //清空排序vector
        Keywords* k = new Keywords(); //暫存k

        vector<string> words; //儲存單字
        words = SpiltText(text); //切割單字

        //查詢關鍵字
        for (auto it = words.begin(); it != words.end(); it++) {
            tempMap.clear();
            string word = *it; //獲得單字

            p = trie->Searching(word); //獲得搜尋結果指針

            //如果正確找到
            if (trie->IsWantedWord(p) == true) {
                p->CountIDF(totalTextNum); //計算此關鍵字的最終idf

#ifdef DEBUG
                cout << word << ": " << p->GetIDF() << endl;
#endif

                //且此關鍵字的idf不等於0
                if (p->GetIDF() != 0) {
                    tempMap = trie->GetSourceMap(p); //獲得此單字的ref of map

                    for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                        //cout << "timesssss" << endl;
                        string key = (*it).first; //取得鍵 (文本id)
                        int occurence = (*it).second; //取得該關鍵字在文本中的出現次數
                        
                        double idf = p->GetIDF(); //取得idf
                        //cout << key << ": " << idf << endl;
                        //cout << key << endl;
                        //cout << wordTotalNum[key] << endl; //test
                        double new_tf = occurence / wordTotalNum[key]; //取得tf
                        //cout << "true" << endl;

                        k->SetValue(idf, new_tf); //生成新的關鍵字資料

                        totalMap[key].push_back(*k); //放進vector中
                        //cout << "test1" << endl;
                    }
                    //cout << "test a" << endl;
                }
            }

            //cout << "testp" << endl;
        }

        //排序每個文本的關鍵字資料
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            sort((*it).second.begin(), (*it).second.end(), Comp2); //排序idf, new_tf

            int recTimes = 0; //已加總的關鍵字數量
            double r; //r value

            cout << "S_ID_" << (*it).first << ": ";

            for (auto p = (*it).second.begin(); p != (*it).second.end()/* && recTimes < 3*/; p++, recTimes++) {
                r += (*p).getIdf() * (*p).getNew_tf(); //累加r值
                cout << (*p).getIdf() << ", " << (*p).getNew_tf();
            }

            cout << endl;

            pair<string, double> eachText;
            eachText.first = (*it).first, eachText.second = r;
            sortingText.push_back(eachText);
        }

        //排序id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //根據knum輸出
        auto it = sortingText.begin(); //指向文本的指針
        int legalNum = sortingText.size(); //符合匹配的文本數量
        for (int i = 0; i < kNum; i++) {
            //如果輸出的數量 少於成功匹配的文本數量 輸出id it++
            if (i < legalNum) {
                cout << (*it).first << ": " << (*it).second;
                it++;
            }
            else cout << "-1"; //不存在則輸出-1

            if (i != kNum - 1) cout << " "; //下一個
                                                                       //不是匹配度>0的vec end pointer
                                                                       //以及knum - 1個
                                                                       //輸出空白
        }

        cout << endl; //換行
    }

    return;
}

bool Comp(pair<string, double> text1, pair<string, double> text2) {
    if (text1.second != text2.second) return text1.second > text2.second;
    else return stoi(text1.first) < stoi(text2.first);
}

//比較關鍵字資料(idf, tf)
bool Comp2(Keywords word1, Keywords word2) {
    double idf1 = word1.getIdf(), idf2 = word2.getIdf();
    double tf1 = word1.getNew_tf(), tf2 = word2.getNew_tf();

    
    //浮點數不相等的話
    if (fabs(idf1 - idf2) > eps) return idf1 > idf2;
    else return (idf1 * tf1) > (idf2 * tf2);
}

void ProductTrie() {
    string text; //儲存每一行的文本

    //從檔案流取出資料 
    while (getline(file, text))
    {
        size_t pos = text.find(','); //找到第一個','的位置
        string id = text.substr(0, pos); //切出id

        TextToTrie(id, text); //樹添加當前文本
        totalTextNum += 1; //文本數量+1
    }
    
    return ;
}

//檢測字元是不是 字母
//如果是 ' ' 保留
bool IsAlpha(char c) {
    if (c == ' ') return false;
    else return !isalpha(c); //如果是字母 回傳false
                             //other true
}

//切割文本
vector<string> SpiltText(string text) {
    vector<string> words; //用於儲存分割後的每個單字

    text.erase(remove_if(text.begin(), text.end(), IsAlpha), text.end()); //把非字母的字元 直接刪除
    
    stringstream ss(text); //將文本放進 字串流
    string token; //暫存單字

    //如果可以從字串流中取出東西
    while (ss >> token) {
        words.push_back(token); //將取出的單字放進words
    }

    return words;
}

//將所有文本中出現的單字 插入樹中
void TextToTrie(string id, string text) {
    vector<string> words = SpiltText(text); //接收 分割文本 回傳的單字vector
    wordTotalNum[id] = words.size(); //紀錄每個文本的總單字數

    //尋訪所有的文字 並一一將其插入到樹中
    for (auto it = words.begin(); it != words.end(); it++) {
        string word = *it; //獲得該指標指向的值 也就是單字
        trie->Insert(word, id); //在目前這棵樹中 插入單字 並記錄來源id
    }
}

//打開檔案
bool OpenFile(string path) {
    file.close();
    file.open(path, ios::in);
    if (!file.is_open()) {
        cout << "file open failure: " << path << endl;
        return false; //檔案沒有正確打開
    }
    return true;
}

//檢查輸入檔案數量
bool ArgcIsWrong(int argc, char** argv) {
    //確認輸入參數數量是否正確（3） 
    if (argc == needFileNum + 1) {
        return false;
    }
    else {
        cout << "Usage: " << argv[0] << "file_path" << endl;
        return true;
    }
}