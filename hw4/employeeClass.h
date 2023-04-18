#ifndef _EMPLOYEECLASS_H
#define _EMPLOYEECLASS_H
#include<string>
#include<iostream>
#include<ctime>
//#include<unordered_map>
using namespace std;

struct WS {
	int sigh;
	double diff;
	
	WS() {
		this->sigh = 0;
		this->diff = 0;
	};
};

class Employee {
public:
	Employee(string id); //construct function
	void Sigh(string date); //該職員 在date打卡
	void Count_Keeping_Day(); //計算該職員連續打卡日
	int MaxingDay_Check(Employee* ep); //計算兩者的連續工作日比較
	void PrintInfo(); //輸出id,工作開始日,工作結束日 資料

	/*void Sigh(string type, string time); //record sign time
	void PrintInfo(); //print info about this employee
	void CountLoading(string date, string timeHM); //if sigh times legal count if this employee overloading*/
private:
	/*struct dailyTime{
		//int times; //record times of sigh
		string lastSighHM; //record last sigh data H:M
		string type; //record last sigh type
	};*/

	static const int SHEET_DAY_NUM = 10000;
	static const int STARTYEAR = 1900, MINUSMON = 1; //tm 的預設從1900開始 月份範圍是0-11
	static constexpr double ONEDAY = (24 * 60 * 60);
	tm ORIGIN_DAY = {}; //紀錄最早能打卡的時間

	string id; //employee ID
	int max_Keeping_Day; //紀錄最長的連續工作日
	struct WS workingSheet[SHEET_DAY_NUM]; //作為紀錄的打卡表
	int startDay, endDay; //紀錄開工日 結束日的index

	/*int overloadingDays; //numbers of days which woking more than 8hr
	int sighForgetDays; //numbers of days which forget to sigh in or sigh out
	unordered_map<string, dailyTime> sighMap; //map of day and sigh in or sigh out situation*/
};

#endif
