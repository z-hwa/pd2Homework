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

	//��l�Ƴ̦����i�ॴ�d���� 20120101
	this->ORIGIN_DAY.tm_year = 2012 - STARTYEAR;
	this->ORIGIN_DAY.tm_mon = 1 - MINUSMON;
	this->ORIGIN_DAY.tm_mday = 1;

	/*this->overloadingDays = 0;
	this->sighForgetDays = 0;*/
}

void Employee::Sigh(string date) {

	//�qdate�� ���ΥX�~��� date: 20121016
	int year = stoi(date.substr(0, 4));
	int month = stoi(date.substr(4, 2));
	int day = stoi(date.substr(6, 2));

	//�����e�ɶ�
	tm nowCheck = {};
	nowCheck.tm_year = year - STARTYEAR;
	nowCheck.tm_mon = month - MINUSMON;
	nowCheck.tm_mday = day;

	//�ഫ��time_t����
	time_t nowTime = mktime(&nowCheck);
	time_t originTime = mktime(&ORIGIN_DAY);

	//�p���Ʈt
	double diff = difftime(nowTime, originTime);

	//��^�Ѽ� �@��index�ϥ�
	int index = diff / ONEDAY;

	workingSheet[index].sigh = 1; //�N��ӤѦ��W�Z
	workingSheet[index].diff = diff; //�O�d��l�ɶ��t
	return;
}

void Employee::Count_Keeping_Day() {
	int nowCount = 0; //�p���U�֭p���W�Z��
	int nowSt = 0; //�p���U�ֿn���}�l��

	for (int i = 0; i < SHEET_DAY_NUM; i++) {

		if (workingSheet[i].sigh == 1) {
			//�p�G�Q��l�� �b�����}�l��
			if (nowSt == 0) nowSt = i;
			nowCount++;
		}
		else {
			//�p�G�o�ӤH���g���⦸�s��u�@�ѼƳ��O�̰�,
			//���n�������@���H
			//�ثe�O�����̾a��2023���@��
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

//�����̤������s��u�@��
int Employee::MaxingDay_Check(Employee* ep) {
	if (this->max_Keeping_Day == ep->max_Keeping_Day) return -1;
	else if (this->max_Keeping_Day > ep->max_Keeping_Day) return 1;
	else return 0;
}

void Employee::PrintInfo() {

	time_t originTime = mktime(&ORIGIN_DAY); //20120101

	time_t stS = workingSheet[startDay].diff;
	time_t edS = workingSheet[endDay].diff;

	time_t stT = stS + originTime; //�Z��19000101����� �i�H��^�h
	time_t edT = edS + originTime;

	struct tm* st, * ed;

	st = localtime(&stT); //tm�������ɶ�

	cout << id << "," << max_Keeping_Day << "," << st->tm_year + STARTYEAR << setw(2) << setfill('0') << right << st->tm_mon + MINUSMON << setw(2) << setfill('0') << right << st->tm_mday;

	ed = localtime(&edT);
	cout << "," << ed->tm_year + STARTYEAR << setw(2) << setfill('0') << right << ed->tm_mon + MINUSMON << setw(2) << setfill('0') << right << ed->tm_mday << endl;
}