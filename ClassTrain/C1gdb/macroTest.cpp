#include<iostream>
using namespace std;

int main() {

	cout << "Test message" << endl;

	int sum;

	for (int i = 0; i < 10; i++) {

#ifdef DEBUG //�ϥΥ������w�q �ӧ@��debug
			//�~���w�q���ɭ� �����n�����sĶ�s�� �_�h�S���ĪG 
		cout << "i=" << i << ", sum=" << sum << endl;
#endif

		sum += 1;
	}

	cout << sum << endl;

	return 0;
}