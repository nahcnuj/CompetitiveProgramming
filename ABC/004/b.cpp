#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

const int INF = 1e8;

int main() {
    string S[4][4];
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            cin >> S[x][y];
        }
    }
    for (int y = 3; y >= 0; --y) {
        for (int x = 3; x >= 0; --x) {
            cout << S[x][y];
            if (x > 0) cout << ' ';
        }
        cout << endl;
    }
    return 0;
}
