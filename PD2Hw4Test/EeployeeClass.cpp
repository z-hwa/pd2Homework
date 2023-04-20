#include"EmployeeClass.h"
#include<iostream>
#include<ctime>
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
  double sec = alreadyDays * ONEDAY;
  time_t secT = sec; //算出要加多少時間

  //超時回傳true
  if(nowTime + secT > lastTime) return true;
  else return false;
}

void Employee::ResetKeepWorkday(int keepingWorkDays) {
  

  return ; 
}