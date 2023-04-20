#include<iostream>
#include"employeeClass.h"
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

//init
Employee::Employee(string id) {
	this->id = id;
	this->overloadingDays = 0;
	this->sighForgetDays = 0;
}

void Employee::Sigh(string type, string time) {
	string date = time.substr(0, 8); //copy date from time like 20170105

	//第一次在打卡系統出現紀錄(在map中沒有找到)
	if(sighMap.count(date) == 0) {
		dailyTime dt; //建立對該筆紀錄的daliyTime
		dt.lastSighHM = time.substr(8, 4); //設定當天日期的打卡時間 ex: 1205
		dt.type = type; //設定類型為type
		sighMap[date] = dt; //添加該筆紀錄到map中

		sighForgetDays++; //先添加忘記第二次打卡的可能性,
				  //如果有第二次在消除
	}else {
		//第二次出現在打卡系統
		sighForgetDays--; //刪除預先加上的忘記紀錄

		CountLoading(date, time.substr(8, 4)); //計算是否超時工作
	}
}

void Employee::PrintInfo() {
	cout << id << "," << overloadingDays << "," << sighForgetDays << endl;
}

void Employee::CountLoading(string date, string timeHM) {
	//轉化小時 和 分為數字
	int lastH = stoi(sighMap[date].lastSighHM.substr(0, 2));
	int lastM = stoi(sighMap[date].lastSighHM.substr(2, 2));
	int h = stoi(timeHM.substr(0, 2));
	int m = stoi(timeHM.substr(2, 2));

	int workingTime = 0;

	//判斷類型sign-in 代表上次是上班 這次是下班
	if(sighMap[date].type == "sign-in") {
		workingTime = (h-lastH)*60 + (m-lastM);
	}else {
		workingTime = (lastH-h)*60 + (lastM-m);
	}
	

	//確認是否超時工作
	if(workingTime > 8*60) {
		overloadingDays++;
	}
}
