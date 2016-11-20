#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;
	cin >> a >> b;
	cout << min(abs(a)+abs(a-b)+abs(b), abs(b)+abs(b-a)+abs(a)) << endl;
	return 0;
}
