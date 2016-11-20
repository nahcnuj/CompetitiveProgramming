#include <iostream>
#include <string>
using namespace std;

int main()
{
	char X;
	string str;
	cin >> X >> str;
	for (int i = 0; i < str.size(); ++i) if (str[i] != X) cout << str[i];
	cout << endl;
	return 0;
}