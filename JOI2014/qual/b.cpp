#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int N, M, A[100], B[100] = {};
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int t;
		cin >> t;
		A[i] = t;
	}
	for (int i = 0; i < M; ++i) {
		int o = 0;
		for (int j = 0; j < N; ++j) {
			int t;
			cin >> t;
			o += (t==A[i] ? (++B[j],0) : 1);
		}
		B[A[i]-1] += o;
	}
	for (int i = 0; i < N; ++i) {
		cout << B[i] << endl;
	}
	return 0;
}
