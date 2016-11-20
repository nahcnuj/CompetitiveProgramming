#include <iostream>
#include <string>
using namespace std;

int main()
{
	string a;
	cin >> a;
	for (int i = 0; i <= a.size()/2; ++i) {
		if (a[i] != a[a.size()-i-1]) {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}
