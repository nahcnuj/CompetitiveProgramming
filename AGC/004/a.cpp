#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	long long int a, b, c;
	cin >> a >> b >> c;
	if (a % 2 && b % 2 && c % 2) {
		cout << min({ a*b, b*c, c*a }) << endl;
	}
	else {
		cout << 0 << endl;
	}

	return 0;
}