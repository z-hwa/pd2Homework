#include<iostream>
#include"Trie.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<utility>
using namespace std;

const int needFileNum = 3; //需要的檔案數量
Trie* trie = new Trie(); //搜尋引擎的樹本體
fstream file; //用於存取檔案的流

double totalTextNum = 0; //所有文本數量
int kNum = 0; //查詢結果輸出數量

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

    unordered_map<string, double> totalMap; //加總出現的文本 IDF總和
    unordered_map<string, int> tempMap; //紀錄指向特定關鍵字的map的ref

    vector<pair<string, double>> sortingText; //用於排序text

    //從檔案流取出資料 以 行 為處理單位 
    while (getline(file, text))
    {
        totalMap.clear(); //對新的提問 更新計算IDF的map
        sortingText.clear(); //清空排序vector

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
                tempMap = trie->GetSourceMap(p); //獲得此單字的ref of map

                for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                    string key = (*it).first; //取得鍵 (id)

                    //.count回傳1 代表找到 所以+idf
                    if (totalMap.count(key) == 1) totalMap[key] += p->GetIDF(); 
                    else totalMap[key] = p->GetIDF();
                }
            }
        }

        //total map 轉移到 排序vecter
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            pair<string, double> eachText;
            eachText.first = (*it).first, eachText.second = (*it).second;
            sortingText.push_back(eachText);
        }

        //排序id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //如果沒有找到
        if (sortingText.size() == 0) cout << "沒有任何文本匹配任一關鍵字";
        else {
            int outNum = 0; //紀錄已經輸出的數量
            
            //輸出id直到符合knum 或是 不存在匹配度>0的文本
            for (auto it = sortingText.begin(); it != sortingText.end() && outNum < kNum; it++, outNum++) {
                cout << (*it).first;
#ifdef IDF
                cout << ":" << (*it).second;
#endif // IDF

                if (it + 1 != sortingText.end() && outNum != kNum) cout << " "; //下一個
                                                                                    //不是匹配度>0的vec end pointer
                                                                                    //以及knum最後一個
                                                                                    //輸出空白
            }
        }

        cout << endl; //換行
    }

    return;
}

//比較函數 (id descending order)
/*bool Comp(string id1, string id2) {
    return stoi(id1) <= stoi(id2);
}
*/
bool Comp(pair<string, double> text1, pair<string, double> text2) {
    if (text1.second != text2.second) return text1.second > text2.second;
    else return stoi(text1.first) < stoi(text2.first);
}

//完全匹配查詢
/*
void FulllyMapSearch() {
    string text; //儲存每一行的文本
    TrieNode* p; //用於存取節點的指針
    
    unordered_map<string, int> totalMap; //加總出現的文本 符合的關鍵字次數
    unordered_map<string, int> tempMap; //紀錄指向特定關鍵字的map的ref
    
    vector<string> sortingText; //用於排序text

    //從檔案流取出資料 以 行 為處理單位 
    while (getline(file, text))
    {
        totalMap.clear(); //對新的提問 更新計算數量的map
        sortingText.clear(); //清空

        vector<string> words; //儲存單字
        words = SpiltText(text); //切割單字
    
        //查詢關鍵字
        for (auto it = words.begin(); it != words.end(); it++) {
            tempMap.clear();
            string word = *it; //獲得單字
            
            p = trie->Searching(word); //獲得搜尋結果指針

            //如果正確找到
            if (trie->IsWantedWord(p) == true) {
                tempMap = trie->GetSourceMap(p);

                for (auto it = tempMap.begin(); it != tempMap.end(); it++) {
                    string key = (*it).first; //取得鍵
                    //int values = (*it).second; //取得值

                    //.count回傳1 代表找到 所以+1 因為是檢查key的文本存不存在當前關鍵字
                    if (totalMap.count(key) == 1) totalMap[key] += 1;
                    else totalMap[key] = 1;
                }
            }
        }

        int keyWordNum = words.size(); //獲得關鍵字數量
        
        //查詢total map數量符合 就放進排序vec中
        for (auto it = totalMap.begin(); it != totalMap.end(); it++) {
            string key = (*it).first; //獲得key (text id)
            //cout << key << ":" << totalMap[key] << endl;
            if (totalMap[key] == keyWordNum) {
                sortingText.push_back(key);
            }
        }

        //排序id
        sort(sortingText.begin(), sortingText.end(), Comp);

        //如果沒有找到
        if (sortingText.size() == 0) cout << -1;
        else {
            //輸出找到的id
            for (auto it = sortingText.begin(); it != sortingText.end(); it++) {
                cout << (*it);
                if (it + 1 != sortingText.end()) cout << " ";
            }
        }

        cout << endl; //換行
    }

    return ;
}
*/

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