#ifndef _EMPLOYEECLASS_H
#define _EMPLOYEECLASS_H
#include<string>
#include<unordered_map>
using namespace std;

class Employee {
	public:
		Employee(string id); //construct function
		void Sigh(string type, string time); //record sign time
		void PrintInfo(); //print info about this employee
		void CountLoading(string date, string timeHM); //if sigh times legal count if this employee overloading
	private:
		struct dailyTime{
			//int times; //record times of sigh
			string lastSighHM; //record last sigh data H:M
			string type; //record last sigh type
		};

		string id; //employee ID
		int overloadingDays; //numbers of days which woking more than 8hr
		int sighForgetDays; //numbers of days which forget to sigh in or sigh out
		unordered_map<string, dailyTime> sighMap; //map of day and sigh in or sigh out situation

};

#endif
