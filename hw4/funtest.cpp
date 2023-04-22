#include<iostream>
#include<string>
#include<ctime>
using namespace std;

int year, month, day;

int main() {

	cin >> year >> month >> day;
	struct tm* t, *t1;
	t->tm_year = 2012 - 1900;
	t->tm_mon = 0;
	t->tm_mday = 0;

	t1->tm_year = year - 1900;
	t1->tm_mon = month - 1;
	t1->tm_mday = day;


	time_t oriT, lastT;
	oriT = mktime(t);

	lastT = mktime(t1);

	cout << (lastT - oriT) / (3600 * 24) << endl;

	return 0;
}
