#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n,m,pt=0;
	vector<int> p;
	cin >>n>>m;
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		p.push_back(t);
	}
	for (int i = 0; i < m; ++i) {
		int t;
		cin >> t;
		pt+=p[t-1];
	}
	cout << pt << endl;
	return 0;
}
