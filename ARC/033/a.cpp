#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int s = 0;
	for (; n > 0; --n) s += n;
	cout << s << endl;
	return 0;
}
