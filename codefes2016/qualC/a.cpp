#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s, t = "CF";
	cin >> s;
	int x = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == t[x]) ++x;
		if (x >= 2) {
			cout << "Yes" << endl;
			return 0;
		}
	}
	cout << "No" << endl;

	return 0;
}