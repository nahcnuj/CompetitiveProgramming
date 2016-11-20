#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int H,W;
	char M[100][100];
	cin >> H >> W;
	for (int y = 0; y < H; ++y) {
		for (int x = 0; x < W; ++x) {
			cin >> M[x][y];
		}
	}
	for (int y = 0; y < H; ++y) {
		int c = -1;
		for (int x = 0; x < W; ++x) {
			if (M[x][y] == 'c') {
				c = x;
				cout << 0;
			}
			else if (c == -1) {
				cout << -1;
			}
			else {
				cout << x-c;
			}
			if (x < W-1) cout << " ";
		}
		cout << endl;
	}
	return 0;
}
