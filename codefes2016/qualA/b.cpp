#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, r = 0;
	vector<int> a;
	cin >> n;
	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		a.push_back(x-1);
	}
	for (int i = 0; i < n; ++i) {
		if (i < a[i] && a[a[i]] == i) ++r;
	}

	cout << r << endl;

	return 0;
}