#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, s = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) s+=i+1;
	if (s == 1) {cout << "BOWWOW" << endl;return 0;}
	for (int i = 2; i*i < s; ++i) {
		if (s % i == 0) {
			cout << "BOWWOW" << endl;
			return 0;
		}
	}
	cout << "WANWAN" << endl;
	return 0;
}
