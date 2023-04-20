#include<iostream>
#include<string>
#include<ctime>
#include<iomanip>
#include"employeeClass.h"
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
	return;
}

void Employee::Count_Keeping_Day() {
	int nowCount = 0; //計算當下累計的上班日
	int nowSt = 0; //計算當下累積的開始日

	for (int i = 0; i < SHEET_DAY_NUM; i++) {

		if (workingSheet[i].sigh == 1) {
			//如果被初始化 在紀錄開始日
			if (nowSt == 0) nowSt = i;
			nowCount++;
		}
		else {
			//如果這個人曾經有兩次連續工作天數都是最高,
			//那要紀錄哪一次？
			//目前是紀錄最靠近2023的一次
			if (nowCount >= max_Keeping_Day) {
				max_Keeping_Day = nowCount;
				startDay = nowSt;
				endDay = i - 1;
			}
			nowSt = 0;
			nowCount = 0;
		}
	}

	return;
}

//比較兩者之間的連續工作日
int Employee::MaxingDay_Check(Employee* ep) {
	if (this->max_Keeping_Day == ep->max_Keeping_Day) return -1;
	else if (this->max_Keeping_Day > ep->max_Keeping_Day) return 1;
	else return 0;
}

void Employee::PrintInfo() {

	time_t originTime = mktime(&ORIGIN_DAY); //20120101

	time_t stS = workingSheet[startDay].diff;
	time_t edS = workingSheet[endDay].diff;

	time_t stT = stS + originTime; //距離19000101的秒數 可以轉回去
	time_t edT = edS + originTime;

	struct tm* st, * ed;

	st = localtime(&stT); //tm類型的時間

	cout << id << "," << max_Keeping_Day << "," << st->tm_year + STARTYEAR << setw(2) << setfill('0') << right << st->tm_mon + MINUSMON << setw(2) << setfill('0') << right << st->tm_mday;

	ed = localtime(&edT);
	cout << "," << ed->tm_year + STARTYEAR << setw(2) << setfill('0') << right << ed->tm_mon + MINUSMON << setw(2) << setfill('0') << right << ed->tm_mday << endl;
}