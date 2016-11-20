#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	vector<int> h;
	int x;
	cin >> n;
	for (; n>0; --n) {
		cin >> x;
		h.push_back(x);
	}
	cin >> x;
	if (h[0] > x) { cout << 1 << endl; return 0;}
	for (int i = 1; i < h.size(); ++i) if (h[i-1] < x && x < h[i]) {
		cout << i+1 << endl;
		return 0;
	}
	cout << h.size()+1 << endl;
	return 0;
}
