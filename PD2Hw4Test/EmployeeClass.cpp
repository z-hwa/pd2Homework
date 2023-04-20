#include"EmployeeClass.h"
#include<iostream>
#include<ctime>
#include<sstream>
#include<iomanip>
using namespace std;

//init
Employee::Employee(int id) {
	this->id = id;
	//temp為 20120101
	tempTime.tm_year = 2012 - STDYEAR;
	tempTime.tm_mon = 1 - STDMON;
	tempTime.tm_mday = 1;

	nowTime = mktime(&tempTime); //初始化現在的時間

	//temp為 20230426
	tempTime.tm_year = 2023 - STDYEAR;
	 tempTime.tm_mon = 4 - STDMON;
	  tempTime.tm_mday = 26;

	lastTime = mktime(&tempTime); //初始化為最終的時間
	maxKeepingWorkday = 0;
}

//更新現在對於該職員的時間 加上天數
void Employee::RenewNowTime(int alreadyDays) {
	 double sec = alreadyDays * ONEDAY; //計算總共經過多少天 的秒數
	  time_t secT = sec; //轉成time_t格式

	nowTime += secT; //更新現在的時間

	return ;
}

//確認現在的時間 如果再經過pass天
//不會實際加上去
//是否超過最晚簽到時間 true代表超時
bool Employee::OutTimeChecker(int pass) {
	double sec = pass * ONEDAY;
	 time_t secT = sec; //算出要加多少時間

	//超時回傳true
	 if (nowTime + secT > lastTime) {
		 return true;
	 }
	else return false;
}

//更新最長的連續工作天數 開始日 結束日
void Employee::ResetKeepWorkday(int keepingWorkDays) {
  
	maxKeepingWorkday = keepingWorkDays; //更新最長的連續工作日
	startTime = nowTime; //將開始日期 改為現在的時間

	double sec = (keepingWorkDays - 1) * ONEDAY; //計算總共工作多少秒
	time_t secT = sec; //轉成time_t

	endTime = secT + nowTime; //將結束日期 設定

	return ; 
}

//檢查是否為最長的連續工作日 true代表是
bool Employee::KeepWorkdayIsBigger(int keepingWorkDay) {
	
	return keepingWorkDay >= maxKeepingWorkday; //確認是不是最大連續工作天數
												//以最靠近2023的時間為準
}

//根據現在的時間 輸出簽到的紀錄 預設時間為0101;
//id,sigh-type,date(201205120101)
string Employee::SighIn() {
	stringstream ss; //作為中轉的str流
	string record; //作為輸出的string
	struct tm* nowTm = localtime(&nowTime); //轉換現在的時間(秒) 為tm格式
	
	//將該輸出的東西 導入流
	ss << id << ",sign-in," << nowTm->tm_year + STDYEAR << setw(2) << setfill('0') << right << nowTm->tm_mon + STDMON << setw(2) << setfill('0') << right << nowTm->tm_mday << "0101" << endl;
	record = ss.str(); //流轉為string
	return record;
}

//比較this和ep的Keeping workday
//帶int 的是比較相等
//true 相等
bool Employee::CompareKeepWorkday(Employee* ep, int mode) {
	return this->maxKeepingWorkday == ep->maxKeepingWorkday;
}

//比較this和ep的Keeping workday
//true 大於
//false 小於
bool Employee::CompareKeepWorkday(Employee* ep) {
	return this->maxKeepingWorkday > ep->maxKeepingWorkday;
}

//比較this和ep的id
//false 大於
//true 小於
bool Employee::CompareId(Employee* ep) {
	return this->id < ep->id;
}

string Employee::PrintAns() {

	stringstream ss; //作為中轉的str流
	string ans; //作為輸出的string
	struct tm* startTm = localtime(&startTime); //轉換開始的時間(秒) 為tm格式

	//將該輸出的東西 導入流
	ss << id << "," << maxKeepingWorkday << "," << startTm->tm_year + STDYEAR << setw(2) << setfill('0') << right << startTm->tm_mon + STDMON << setw(2) << setfill('0') << right << startTm->tm_mday << ",";
	
	struct tm* endTm = localtime(&endTime); //轉換結束的時間
	ss << endTm->tm_year + STDYEAR << setw(2) << setfill('0') << right << endTm->tm_mon + STDMON << setw(2) << setfill('0') << right << endTm->tm_mday << endl;

	ans = ss.str(); //流轉為string
	return ans;
}



