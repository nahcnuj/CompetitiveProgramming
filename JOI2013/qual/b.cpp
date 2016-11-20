#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
	int N, M, A[1000], B[1000], v[1000] = {}, max = 0, res;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	for (int i = 0; i < M; ++i) {
		cin >> B[i];
		int j = 0;
		while (B[i] < A[j]) ++j;
		++v[j];
	}
	max = v[0]; res = 1;
	for (int i = 1; i < N; ++i) {
		if (v[i] > max) max = v[i], res = i+1;
	}
	cout << res << endl;
	return 0;
}
