#include <bits/stdc++.h>
using namespace std;
int main()
{
	int Q;
	string S,T;
	cin >> Q;
	for (int q = 0; q < Q; ++q) {
		cin >> S >> T;
		vector<char> x;
		for (int i = 0; i < S.length(); ++i) {
			if (T.find(S[i], 0) == string::npos) x.push_back(S[i]);
		}
		string U = "";
		for (int i = 0; i < S.length(); ++i) {
			if (find(x.begin(), x.end(), S[i]) == x.end()) U += S[i];
		}
		if (U.find(T, 0) != string::npos) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
