#include <iostream>
#include <string>
using namespace std;
int main()
{
	string A;
	long long int B;
	cin >> A >> B;
	cout << A[(B-1)%A.length()] << endl;
}