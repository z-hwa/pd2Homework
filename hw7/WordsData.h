#ifndef WORDSDATA
#define WORDSDATA
#include<iostream>
using namespace std;

class Keywords {
public:
	Keywords(); //constructor
	~Keywords(); //destructo

	//�����ظ�T
	double getIdf();
	double getNew_tf();

	//�]�w
	void SetValue(double idf, double new_tf);

private:
	double idf;
	double new_tf;
};

#endif // !WORDSDATA
