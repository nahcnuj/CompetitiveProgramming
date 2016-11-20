#include <iostream>
using namespace std;

int main()
{
	int N, n = 0, a, s = 0;
	cin >> N;
	for (; N > 0; --N) {
		cin >> a;
		if (a>0) s+=a, ++n;
	}
	cout << (int)((double)s/n + .9) << endl;
	return 0;
}