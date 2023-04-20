#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#define NDEBUG
#include<assert.h>
#include"employeeClass.h"
using namespace std;

const int needFileNum = 2;
unordered_map<string, Employee*> employee; //id指向員工的map
vector<pair<string, Employee*> > vec; //用於排序輸出

//比較員工的連續工作天數
//如果相等,以id小的優先
bool Comp(const pair<string, Employee*> p1, const pair<string, Employee*> p2);

//read file
void ReadFile(fstream &file);

//根據需求排序資料
void SortData();

//輸出函數
void OutPut();

int main(int argc, char** argv) {
	//確認輸入參數數量是否正確（2）
	if(argc < needFileNum) {
		cout << "Usage: " << argv[0] << "file_path" << endl;
		return 1;
	}

	string filePath = argv[1];

	fstream file(filePath, ios::in); //開檔

	if(!file.is_open()) {
		cout << "file could not open" << endl;
		return 1; //錯誤 結束程式
	}
	
	ReadFile(file); //讀取資料
	SortData(); //排序資料
	OutPut(); //輸出資料

	return 0;
}

void OutPut() {

	//輸出
	int i = 0;
	for(auto it = vec.begin(); it != vec.end() && i<3; it++, i++) {
		it->second->PrintInfo();
	}
	return ;
}

bool Comp(const pair<string, Employee*> p1, const pair<string, Employee*> p2) {
	int p1Num = stoi(p1.first);
	int p2Num = stoi(p2.first);

	//-1 means it is equal, 1 means bigger, 0 means smaller 
	if(p1.second->MaxingDay_Check(p2.second) != -1) return p1.second->MaxingDay_Check(p2.second);
	else {
		//以id做升序排列
		return p1Num < p2Num;
	}
}

void SortData() {
	
	for(auto ep : employee) {
		ep.second->Count_Keeping_Day(); //在排序之前 算出最久的連續工作天數
		vec.push_back(ep);
	}

	sort(vec.begin(), vec.end(), Comp); //根據id排序

	return ;
}

void ReadFile(fstream &file) {
	
	string record; //每行的紀錄
	
	while(getline(file, record)) {

		//找到兩個,的位置
		size_t pos1 = record.find(',');
		size_t pos2 = record.find(',', pos1+1);

		//獲取一個紀錄的3個data
		string id = record.substr(0, pos1);
		//string type = record.substr(pos1+1, pos2 - pos1 - 1);
		string time = record.substr(pos2+1, sizeof(record) - pos2);

		//第一次出現
		if(employee.count(id) == 0) {
			Employee* ep = new Employee(id);
			ep->Sigh(time);
			employee[id] = ep; //設定first位置為id
		}else {
			employee[id]->Sigh(time); //打卡
		}
	}
}
