#include<iostream>
using namespace std;

int main() {

	cout << "Test message" << endl;

	int sum;

	for (int i = 0; i < 10; i++) {

#ifdef DEBUG //使用巨集的定義 來作為debug
			//外部定義的時候 必須要直接編譯連結 否則沒有效果 
		cout << "i=" << i << ", sum=" << sum << endl;
#endif

		sum += 1;
	}

	cout << sum << endl;

	return 0;
}