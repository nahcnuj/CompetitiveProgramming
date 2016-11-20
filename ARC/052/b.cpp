#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

double v[20000];

int main() {
	int N, Q;
	
	cin >> N >> Q;
	for (int i = 0; i < N; ++i) {
		int x, r, h;
		cin >> x >> r >> h;
		
		for (int j = 0; j < h; ++j) {
			double h1 = h - j, r1 = h1 * r / h;
			double h2 = h - j - 1.0, r2 = h2 * r / h;
			
			v[x + j] += M_PI * (r1 * r1 * h1 - r2 * r2 * h2) / 3.0;
		}
	}
	
	for (int i = 0; i < Q; ++i) {
		int a, b;
		cin >> a >> b;
		
		bool f = false;
		double V = 0;
		for (int j = a; j < b; ++j) {
			V += v[j];
		}
		
		
		printf("%.6f\n", V);
	}
	
	return 0;
}