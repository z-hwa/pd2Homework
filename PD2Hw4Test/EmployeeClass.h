#ifndef _EMPLOYEECLASS_H
#define _EMPLOYEECLASS_H

#include<iostream>
#include<ctime>
#include<string>
using namespace std;

class Employee {
public:
    Employee(int id);   //init
    void RenewNowTime(int alreadyDays); //更新現在對於該職員的時間 加上天數
    bool OutTimeChecker(int pass);  //確認現在的時間 如果再經過pass天
                                    //不會實際加上去
                                    //是否超過最晚簽到時間 true代表超時
    void ResetKeepWorkday(int keepingWorkDays); //更新最長的連續工作天數 開始日 結束日
    bool KeepWorkdayIsBigger(int keepingWorkDays); //檢查是否為最長的連續工作日 true代表是
    string SighIn();    //根據現在的時間 輸出簽到的紀錄 預設時間為0101;
                        //id,sigh-type,date(201205120101)
    //帶int 的是比較相等
    bool CompareKeepWorkday(Employee* ep, int mode); //true 相等
    bool CompareKeepWorkday(Employee* ep);    //比較this和ep的Keeping workday
                                            //true 大於
                                            //false 小於
    bool CompareId(Employee* ep); //比較this和ep的id
                                //false 大於
                                //true 小於
    string PrintAns(); //輸出解答格式
private:
    int id;
    //tm作為類別 標準是從1900開始算 0~11月
    const int STDYEAR = 1900;
    const int STDMON = 1;
    const double ONEDAY = (60 * 60 * 24); //一天的秒數
    tm tempTime = {}; //用於初始化 現在的時間以及最後的時間
    time_t nowTime, lastTime; //紀錄現在的時間 從 20120101
    time_t startTime, endTime; //紀錄最長連續工作區間
    int maxKeepingWorkday; //紀錄最長的連續工作天數
};

#endif