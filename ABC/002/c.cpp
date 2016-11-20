#include <bits/stdc++.h>
using namespace std;
int main() {
	int xa,ya,xb,yb,xc,yc;
	cin>>xa>>ya>>xb>>yb>>xc>>yc;
	int ABx = xb-xa, ABy = yb-ya, ACx = xc-xa, ACy = yc-ya;
	printf("%.1f",abs(ABx*ACy - ACx*ABy) / 2.0);
	return 0;
}
