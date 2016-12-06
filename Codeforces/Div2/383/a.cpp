#include <iostream>
using namespace std;

int main()
{
	int N, ans = 1;
	cin >> N;
	if (N > 0 && N % 4 == 0) N = 4;
	else N %= 4;
	for (int i = 0; i < N; ++i) {
		ans *= 8;
		ans %= 10;
	}
	cout << ans << endl;
	return 0;
}
