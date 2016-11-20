#include <iostream>

using namespace std;

int main() {
	int k, a = 3, b = 0, c;
	cin >> k;
	for (; k > 0; --k) {
		c = a; a = (b==0 ? 2 : 1)*a+b; b = c;
	}
	cout << a << " " << b << endl;
	return 0;
}