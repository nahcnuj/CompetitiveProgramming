#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int A, B, C, D, P;
	cin >> A >> B >> C >> D >> P;
	cout << min(A*P, B + (P<=C ? 0 : D*(P-C))) << endl;
	return 0;
}
