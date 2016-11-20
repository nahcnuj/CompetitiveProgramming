#include <iostream>
#include <string>
using namespace std;
int main() {
	int N, L, i = 1, x = 0;
	string S;
	cin >> N >> L >> S;
	for (auto&& s : S) {
		if (s == '+') { if (++i > L) i = 1, ++x; }
		else --i;
	}
	cout << x << endl;
	return 0;
}
