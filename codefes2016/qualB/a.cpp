#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s, t = "CODEFESTIVAL2016";
	cin >> s;
	int x = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != t[i]) ++x;
	}
	cout << x << endl;

	return 0;
}