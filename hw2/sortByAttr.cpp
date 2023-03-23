#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm> //sort
#include <vector> //vector
#include <fstream> //fstream
#include <sstream> //sstring
using namespace std;

//type for unit career
class Unit{
	public:
		string id; //ID
		int age;
		char gender;
		int salary;
};

//1D-list record every career
vector<Unit> unitList;
int number=0; //record total unit

int GetInput(string filename); //get input
bool CompareUnit(Unit u1, Unit u2); //compare unit fun
void OutPut(); //output answer

int main(int argc, char** argv) {
	int check = 0;

	check = GetInput(argv[1]);	
	if(check == 1 ) return 1; //file could not open

	#ifdef INPUT
		for(int i=0;i<number;i++) {
			cout << unitList[i].id << ":" << unitList[i].age << ", " << unitList[i].gender << ", " << unitList[i].salary << endl;
		}
	#endif

	sort(unitList.begin(), unitList.end(), CompareUnit);

	OutPut();

	return 0;
}

void OutPut() {
	int nowSalary = 0;
	for(int i=0;i<number;i++) {
		//check this salary != now salary then output salary + ','
		if(nowSalary != unitList[i].salary) cout << unitList[i].salary << ',';
		//renew now salary
		nowSalary = unitList[i].salary;
		
		cout << unitList[i].id; //cout id of this unit
		
		//check next one salary == now salary then cout ','
		//else cout endl
		if(i+1 != number && unitList[i+1].salary == nowSalary) cout << ',';
		else cout << endl;
	}

	return ;
}

bool CompareUnit(Unit u1, Unit u2) {
	
	// sort by question
	if(u1.salary != u2.salary) return u1.salary < u2.salary;
	else if(u1.age != u2.age) return u1.age < u2.age;
	else if(u1.gender != u2.gender) return u1.gender == 'f';
	else return u1.id < u2.id;
}

int GetInput(string filename) {
	Unit unit;	//temp record unit data
	stringstream s1;	//sstring which use to cut string
	string tempForS1;	//use to save string from file temporaliy
	
	string fname = filename;	//get file name
	fstream file(fname, ios::in);	//use fstream 'file' to open stream with file 'fname'

	//check the file been open?
	if(file.is_open()) {
		//read row by row of csv data
		while(getline(file, tempForS1)) {
			s1.str(""); 	//use to reset s1's content as ""EOF
			s1.clear(); 	//use to clear the EOF behind the s1's content
					//thus s1 init as ""	
			s1 << tempForS1; //put data in sstring

			string data[4];
			int n=0;
			//read ',' by ',' of row data of csv
			while(getline(s1, data[n], ',')) n++;

			//set data
			unit.id = data[0];
			unit.age = stoi(data[1]);
			unit.gender = data[2][0];
			unit.salary = stoi(data[3]);

			unitList.push_back(unit);
			number++;
		}
	}else {
		cout << "could not open the file" << endl;
		return 1;
	}

	return 0;
}
