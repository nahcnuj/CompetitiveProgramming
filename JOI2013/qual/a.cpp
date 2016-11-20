#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	int a, sum = 0;
	for (int i = 0; i < 5; ++i) {
		cin >> a;
		sum += a >= 40 ? a : 40;
	}
	cout << sum/5 << endl;
	return 0;
}
