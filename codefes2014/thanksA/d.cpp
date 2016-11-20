#include <iostream>
using namespace std;

int main()
{
	int n,q;
	cin>>n>>q;
	long long int a,b,s,t;
	for (int i = 0; i < q; ++i) {
		cin >> a >> b >> s >> t;
		long long int res = 0;
		if (a < s && b < s && b < t) cout << (t-s)*100;
		else if (t < a && s < a && s < b) cout << (t-s)*100;
		else {
			if (a-s > 0) res += (a-s)*100;
			if (t-b > 0) res += (t-b)*100;
			cout << res;
		}
		cout << endl;
	}
	return 0;
}
