#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, a, b;
	string s;
	cin >> n >> a >> b >> s;
	for (int i = 0, x = 0, y = 1; i < n; ++i) {
		if (s[i] == 'a') {
			if (x < a + b) {
				++x;
				cout << "Yes" << endl;
			}
			else cout << "No" << endl;
		}
		else if (s[i] == 'b') {
			if (x < a + b && y <= b) {
				++x;
				cout << "Yes" << endl;
			}
			else cout << "No" << endl;
			++y;
		}
		else cout << "No" << endl;
	}

	return 0;
}