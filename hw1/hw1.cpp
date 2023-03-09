#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n, big=0;

int main(int argc, char** argv) {
	n = atoi(argv[1]);
	for(int i=0;i<=n;i++) {
		printf("(%d,%d)\n", i, n-i);
		
		big=max(big, i*(n-i));
	}
	
	printf("%d\n", big);

	return 0;
}
