#include <iostream>
#include <string>
#include <queue>
#include <utility>
using namespace std;

string flip(const string& s, int n) {
	string r{};
	if (n == -1) n = s.length();
	for (int i = 0; i < n; ++i) {
		r += (s[n - i - 1] == '+' ? '-' : '+');
	}
	return r + s.substr(n);
}

int main() {
	int T;
	string S;
	cin >> T;
	for (int i = 1; i <= T; ++i) {
		cout << "Case #" << i << ": ";
		cin >> S;
		int t = 0;
		while (count(S.begin(), S.end(), '+') < S.length()) {
			S = flip(S, S.find(S[0] == '+' ? '-' : '+'));
			++t;
		}
		cout << t << endl;
	}
	return 0;
}