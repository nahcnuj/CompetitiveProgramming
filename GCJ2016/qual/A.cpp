#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int T, N;
	cin >> T;
	for (int i = 1; i <= T; ++i) {
		cout << "Case #" << i << ": ";
		cin >> N;
		if (N == 0) cout << "INSOMNIA" << endl;
		else {
			bool b[10] = {};
			for (int j = 1; ; ++j) {
				int x = j*N, y = x;
				while (x > 0) {
					b[x % 10] = true;
					x /= 10;
				}
				if (count(begin(b), end(b), true) == 10) {
					cout << y << endl;
					break;
				}
			}
		}
	}
	return 0;
}