#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n,a[3],s=0,t=0,mi=1e7;
	cin >> n>>a[0]>>a[1]>>a[2];
	for (int i = 0; i < 3; ++i) {
		s=0;
		for (t = 0; s < n; ++t) {
			s+=a[(t+i)%3];
		}
		mi = min(t,mi);
	}
	cout << mi << endl;
	return 0;
}
