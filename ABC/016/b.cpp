#include <iostream>
using namespace std;
int main()
{
	int a,b,c;
	cin >> a >> b >> c;
	if (a+b == c) {
		if (a-b == c) cout << "?";
		else cout << "+";
	}
	else if (a-b == c) cout << "-";
	else cout << "!";
	cout << endl;

	return 0;
}
