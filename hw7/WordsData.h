#ifndef WORDSDATA
#define WORDSDATA
#include<iostream>
using namespace std;

class Keywords {
public:
	Keywords(); //constructor
	~Keywords(); //destructo

	//獲取兩種資訊
	double getIdf();
	double getNew_tf();

	//設定
	void SetValue(double idf, double new_tf);

private:
	double idf;
	double new_tf;
};

#endif // !WORDSDATA
