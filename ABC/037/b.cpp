#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, q, l, r, t;
	cin >> n >> q;
	vector<int> a(n,0);
	for (; q > 0; --q) {
		cin >> l >> r >> t;
		for (int i = l-1; i < r; ++i) a[i] = t;
	}
	for (auto&& x : a) cout << x << endl;
	return 0;
}
