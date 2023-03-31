#include<iostream>
#include<unordered_map>
#include"employeeClass.h"
using namespace std;

unordered_map<string, Employee*> employee; //id指向員工的map

int main() {
	string id = "1032";
	Employee* ep = new Employee(id);
	employee[id] = ep;

	employee[id]->Sigh("sigh-in", "201301050808");
	employee[id]->Sigh("sigh-out", "201301051905");

	employee[id]->PrintInfo();

	return 0;
}
