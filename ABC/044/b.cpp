#include <iostream>
#include <string>
using namespace std;

int main()
{
	int c[30] = {};
	string w;
	cin >> w;
	for (int i = 0; i < w.length(); ++i) {
		++c[w[i] - 'a'];
	}
	for (int i = 0; i < 30; ++i) {
		if (c[i] % 2 != 0) {
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;

	return 0;
}