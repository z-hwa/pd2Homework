#include<iostream>
#include"employeeClass.h"
#include<string>
#include<ctime>
//#include<unordered_map>
//#include<vector>
//#include<algorithm>
using namespace std;
//init
Employee::Employee(string id) {
	this->id = id;
	this->max_Keeping_Day = 0;
	this->startDay = 0;
	this->endDay = 0;
	
	//初始化最早的可能打卡紀錄 20120101
	this->ORIGIN_DAY.tm_year = 2012 - STARTYEAR;
	this->ORIGIN_DAY.tm_mon = 1 - MINUSMON;
	this->ORIGIN_DAY.tm_mday = 1;

	/*this->overloadingDays = 0;
	this->sighForgetDays = 0;*/
}

void Employee::Sigh(string date) {

	//從date中 切割出年月日 date: 20121016
	int year = stoi(date.substr(0, 4));
	int month = stoi(date.substr(4, 2));
	int day = stoi(date.substr(6, 2));

	//獲取當前時間
	tm nowCheck = {};
	nowCheck.tm_year = year - STARTYEAR;
	nowCheck.tm_mon = month - MINUSMON;
	nowCheck.tm_mday = day;

	//轉換為time_t類型
	time_t nowTime = mktime(&nowCheck);
 	time_t originTime = mktime(&ORIGIN_DAY);

	//計算秒數差
	double diff = difftime(nowTime, originTime);

	//轉回天數 作為index使用
	int index = diff / ONEDAY;

	workingSheet[index].sigh = 1; //代表該天有上班
	workingSheet[index].diff = diff; //保留原始時間差
	return ;
}

void Employee::Count_Keeping_Day() {
	int nowCount = 0; //計算當下累計的上班日
	int nowSt = 0; //計算當下累積的開始日

	for(int i=0;i<SHEET_DAY_NUM;i++) {

		if(workingSheet[i].sigh == 1) {
			//如果被初始化 在紀錄開始日
			if(nowSt == 0) nowSt = i;
			nowCount++;
		}
		else {
			//如果這個人曾經有兩次連續工作天數都是最高,
			//那要紀錄哪一次？
			//目前是紀錄最早的一次
			if(nowCount > max_Keeping_Day) {
				max_Keeping_Day = nowCount;
				startDay = nowSt;
				endDay = i-1;
			}
			nowSt = 0;
			nowCount = 0;
		}
	}

	return ;
}

//比較兩者之間的連續工作日
int Employee::MaxingDay_Check(Employee* ep) {
	if(this->max_Keeping_Day == ep->max_Keeping_Day) return -1; 
	else if(this->max_Keeping_Day > ep->max_Keeping_Day) return 1;
	else return 0;
}

void Employee::PrintInfo() {

	time_t originTime = mktime(&ORIGIN_DAY); //20120101

	time_t stS = workingSheet[startDay].diff;
	time_t edS = workingSheet[endDay].diff ;
	
	time_t stT = stS + originTime; //距離19000101的秒數 可以轉回去
	time_t edT = edS  + originTime;

	struct tm *st, *ed;

	st = localtime(&stT); //tm類型的時間

	cout << id << "," << max_Keeping_Day << "," << st->tm_year + STARTYEAR << st->tm_mon + MINUSMON << st->tm_mday;

	ed = localtime(&edT);
	cout << "," << ed->tm_year + STARTYEAR << ed->tm_mon + MINUSMON << ed->tm_mday  << endl;
}

/*
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
}*/
