#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	int i = 0;
	while (cin >> s) {
		if (i > 0) cout << " ";
		if (s == "Left") cout << "<";
		if (s == "Right") cout << ">";
		if (s == "AtCoder") cout << "A";
		++i;
	}
	cout << endl;
	return 0;
}
