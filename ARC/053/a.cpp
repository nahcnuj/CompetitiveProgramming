#include <iostream>
#include <string>

using namespace std;

int main() {
	int H, W;
	cin >> H >> W;
	cout << H * (W - 1) + W * (H - 1) << endl;
	return 0;
}