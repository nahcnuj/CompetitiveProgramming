#include <iostream>
using namespace std;

int main()
{
	int K, N;
	int T[5][5];
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) cin >> T[i][j];
	}
	int a[5] = {};
	int x = 1;
	for (int i = 0; i < N; ++i) x *= K;
	for (int i = 0; i < x; ++i) {
		int s = T[0][a[0]];
		cerr << a[0] << " ";
		for (int j = 1; j < N; ++j) {
			cerr << a[j] << " ";
			s ^= T[j][a[j]];
		}
		cerr << endl;
		if (s == 0) {
			cout << "Found" << endl;
			return 0;
		}
		
		++a[0];
		int j = 0;
		while (a[j] >= K) {
			a[j++] = 0;
			++a[j];
		}
	}
	
	cout << "Nothing" << endl;
	return 0;
}