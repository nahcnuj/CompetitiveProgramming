#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, M, a, b;
	bool v[100000] = {};
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		v[a-1] = true;
		v[b-1] = true;
	}
	int x = 0;
	for (int i = 0; i < N; ++i) {
		if (v[i]) ++x;
	}
	cout << N-x << endl;
	return 0;
}
