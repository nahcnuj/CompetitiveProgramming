#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int x = 0, n = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s.substr(i,2) == "25") {
			++n;
			++i;
		}
		else {
			for (int j = n; j > 0; --j) {
				x+=j;
			}
			n = 0;
		}
	}
	if (n > 0) {
		for (int j = n; j > 0; --j) {
			x+=j;
		}
	}
	cout << x << endl;
	return 0;
}
