#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int T;
	string S;


	int y[][5] = { { 0,2,4,6,8 },{ 1,3,5,7 } };
	string a[] = { "ZWUXG", "OTFS" };
	string b[][5] = { { "ERO", "TO", "FOR", "SI", "EIHT" },{ "NE","HREE","IVE","EVNE" } };

	cin >> T;
	for (int i = 1; i <= T; ++i) {
		int x[26] = {};
		cin >> S;

		for (int j = 0; j < S.size(); ++j) {
			++x[S[j] - 'A'];
		}
		
		int res[10] = {};

		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < a[j].size(); ++k) {
				while (x[a[j][k] - 'A'] > 0) {
					++res[y[j][k]];
					--x[a[j][k] - 'A'];
					for (int h = 0; h < b[j][k].size(); ++h) {
						--x[b[j][k][h] - 'A'];
					}
				}
			}
		}
		res[9] = x['E' - 'A'];

		cout << "Case #" << i << ": ";
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < res[j]; ++k) cout << j;
		}
		cout << endl;
	}
	return 0;
}