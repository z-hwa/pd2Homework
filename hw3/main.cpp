#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include"employeeClass.h"
using namespace std;

unordered_map<string, Employee*> employee; //id指向員工的map

bool comp(pair<string, Employee*> p1, pair<string, Employee*> p2) {
	int p1Num = stoi(p1.first);
	int p2Num = stoi(p2.first);
	return p1Num < p2Num;
}

int main(int argc, char** argv) {
	//確認是否正確輸入參數
	if(argc < 2) {
		cout << "Usage: " << argv[0] << "file_path" << endl;
		return 1;
	}
	
	string filePath = argv[1]; //設定檔案路徑
	
	fstream file(filePath, ios::in); //讀檔

	if(!file.is_open()) {
		cout << "file could not open" << endl;
		return 1;
	}
	string record; //每行的紀錄
	
	while(getline(file, record)) {
		//找到兩個,的位置
		size_t pos1 = record.find(',');
		size_t pos2 = record.find(',', pos1+1);

		//獲取一個紀錄的3個data
		string id = record.substr(0, pos1);
		string type = record.substr(pos1+1, pos2 - pos1 - 1);
		string time = record.substr(pos2+1, sizeof(record) - pos2);

		//第一次出現
		if(employee.count(id) == 0) {
			Employee* ep = new Employee(id);
			ep->Sigh(type, time);
			employee[id] = ep;
		}else {
			employee[id]->Sigh(type, time); //打卡
		}
	}

	vector<pair<string, Employee*> > vec; //用於排序輸出
	
	for(auto ep : employee) {
		vec.push_back(ep);
	}

	sort(vec.begin(), vec.end(), comp); //根據id排序
	
	//輸出
	for(auto it = vec.begin(); it != vec.end(); it++) {
		it->second->PrintInfo();
	}

	return 0;
}
