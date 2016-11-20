#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n,k;
	cin >> n >> k;
	vector<int> a;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	long long int s = 0;
	for (int i = 0; i < k; ++i) s += a[i];
	long long int S = s;
	for (int i = 1; i <= n - k; ++i) S += (s += -a[i-1] + a[i+k-1]);
	cout << S << endl;
	return 0;
}
