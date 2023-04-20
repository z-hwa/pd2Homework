#include<iostream>
#include<fstream>
#include"EmployeeClass.h"
#include<ctime>
#include<vector>
using namespace std;

int peopleNumber = 0, recUpper = 0; //存放要生成的人數 以及記錄組數
int needFileNum = 3; //需要的檔案數
fstream file; //使用的流
vector<Employee*> vec; //儲存每個職員

bool ArgcIsWrong(int argc, char** argv);
void UserInput();
bool OpenFile(string path);
void PrductPeople();
void ProductRec(Employee* ep, int recNumber);
void SighByDay(Employee* ep, int keepingWorkDays);
void Sort();
bool comp(Employee* ep1, Employee* ep2);
void OutPutAns();

int main(int argc, char** argv) {

  if(ArgcISWrong(int argc, char** argv)==true) {return 1;} //檢查參數數量是否錯誤
  UserInput(); //使用者輸入
  if(OpenFile(argv[1]) == false) {return 1;} //根據path打開檔案
  ProductPeople(); //生成簽到紀錄
  Sort(); //排序 找出最大的那三個
  if(OpenFile(argv[2]) == false) {return 1;} //打開輸出解答的檔案
  OutPutAns(); //輸出解答

  return 0;
}

//輸出解答
void OutPutAns(){

  for(Employee* it = vec.begin();it != vec.end();it++) {
    file << it->PrintAns();
  }

  return ;
}

//排序規則
bool comp(Employee* ep1, Employee* ep2) {
  if(ep1->CompareKeepWorkday(ep2, 0) != true) return ep1->CompareKeepWorkday(ep2);
  else retunr ep1->CompareId(ep2);
}

void Sort(){
  sort(vec.begin(), vec.end(), comp); //排序
  return ;
} 

void ProductPeople() {
  int nowId = 0
  for(int i=0;i<peopleNumber;i++) {
    int addId = 7; //亂數生成id變量（1, 1000)
    int recNumber = 199; //亂數生成記錄組數（1, recUpper）

    nowId += addId; //更新當前id
    Employee* ep = new Employee(id); //創建該職員的類別

    ProductRec(ep, recNumber); //創建該職員的簽到紀錄

    vec.push_back(ep); //把職員放進vec
  }

  return;
}

//根據keepingWorkDays來生成簽到記錄
void SighByDay(Employee* ep, int keepingWorkDays) {
  for(int i=0;i<keepingWorkDays;i++) {
    //輸出簽到記錄 到流裡 id,sigh-type,date
    file << ep->SighIn();
    ep->RenewNowTime(1); //到下一天
  }

  return ;
}

//根據需要的record number生成紀錄筆數
void ProductRec(Employee* ep, int recNumber) {
  int alreadyDays = 10; //亂數生成經過的天數 (1, ...)
  ep->RenewNowTime(alreadyDays); //更新經過的天數
  //True: 超時
  if(ep->OutTimeChecker(0) == true) {return ;} //確認是否超時 因為已經加上去了 所以檢查時的增加值帶0就可以了

  int keepingWorkDays = 9; //亂數生成連續工作天數 (1, ...)
  if(ep->OutTimeChecker(keepingWorkDays) == true) {return ;} //檢測超時

  if(ep->KeepWorkdayIsBigger(keepingWorkDays) == true) ep->ResetKeepWorkday(keepingWorkDays); //如果是最長的連續工作日 更新employee的開始結束 最長連續工作日

  void SighByDay(ep, keepingWorkDays); //簽到

  return ;
}

//打開檔案
bool OpenFile(string path) {
  file.Open(path, ios::out);
  if(!file.is_open()) {
    cout << "file open failure: " << path << endl;
    return false; //檔案沒有正確打開
  }
  return true;
}

//使用者輸入
void UserInput() {
  cin >> peopleNumber >> recUpper;
  return ;
}

bool ArgcIsWrong(int argc, char** argv) {
  //確認輸入參數數量是否正確（3） 
  if(argc < needFileNum) { 
    cout << "Usage: " << argv[0] << "file_path" << endl; 
    return false;
  }
}