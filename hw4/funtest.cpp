#include<iostream>
#include<string>
#include<ctime>
using namespace std;

class Employee {
public:
	Employee();
	tm origin = {};
};

Employee::Employee() {
	origin.tm_year = 2012;
}

Employee* ep = new Employee();

int main() {

	cout << ep->origin.tm_year << endl;

	return 0;
}
