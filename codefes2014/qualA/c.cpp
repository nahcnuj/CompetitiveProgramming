#include <iostream>
using namespace std;
int main()
{
	long long int A, B, cnt=0;
	cin >> A >> B;
	for (int i = A + (A%4!=0 ? (4-A%4) : 0); i <= B; i+=4) {
		if (i % 4 == 0 && (i % 100 != 0 || i % 400 ==0)) ++cnt;
	}
	cout << cnt << endl;
}