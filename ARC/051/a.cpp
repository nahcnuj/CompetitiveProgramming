#include <iostream>

using namespace std;

int main() {
	int x1,y1,r,x2,y2,x3,y3;
	bool br = false, bb = false;
	
	cin >> x1 >> y1 >> r;
	cin >> x2 >> y2 >> x3 >> y3;
	for (int y = -100; y <= 100; ++y) {
		for (int x = -100; x <= 100; ++x) {
			if ((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y) <= r*r) {
				if (!(x2 <= x && x <= x3 && y2 <= y && y <= y3)) br = true;
			}
			else if (x2 <= x && x <= x3 && y2 <= y && y <= y3) bb = true;
		}
	}
	cout << (br ? "YES" : "NO") << endl << (bb ? "YES" : "NO") << endl;
	return 0;
}