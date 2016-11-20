#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

int main()
{
	int n, m, x = 0, y = 0;
	set<int> a;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		a.insert(t);
		++x;
	}
	for (int i = 0; i < m; ++i) {
		int t;
		cin >> t;
		if (a.count(t) > 0) {++y;}
		else ++x;
	}
	printf("%.7f\n", (double)y/x);
	return 0;
}
