	#include <bits/stdc++.h>
	using namespace std;
	int main()
	{
		int a[2],b[2],c;
		cin>>a[0]>>a[1]>>b[0]>>b[1]>>c;
		vector<int> x;
		for (int i = 0; i < 2;++i) {
			for (int j = 0; j < 2; ++j) {
				if (a[i] == c && find(x.begin(),x.end(),b[j])==x.end()) x.push_back(b[j]);
				else if (b[j] == c && find(x.begin(),x.end(),a[i])==x.end()) x.push_back(a[i]);
			}
		}
		cout << x.size() << endl;
		sort(x.begin(),x.end());
		for (int i = 0; i < x.size(); ++i) {
			cout << x[i] << endl;
		}
		return 0;
	}
