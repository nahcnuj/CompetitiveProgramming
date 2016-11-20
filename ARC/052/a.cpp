#include <iostream>
#include <string>

using namespace std;

int main() {
	string id;
	cin >> id;
	
	for (auto c : id) {
		if ('0' <= c && c <= '9') cout << c;
	}
	cout << endl;
	
	return 0;
}