#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	const double eps = 1e-14;
	double r, n, m;
	cin >> r >> n >> m;
	vector<double> l;
	for (int i = -m; i <= n + m - 1; ++i) {
		if (0 <= i && i <= n) {
			double y = abs(2 * i - n) * r / n;
			double x2 = r*r - y*y;
			l.push_back(2 * sqrt(x2));
		}
		else {
			l.push_back(0);
		}
	}
	double s = 0;
	for (int i = 1; i <= n + m - 1; ++i) {
		s += max(l[i+m], l[i]);
	}
	printf("%.10f\n", s);
	return 0;
}
