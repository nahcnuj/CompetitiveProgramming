#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

const int INF = 1e8;
const int MOD = 1e9 + 7;

template<typename T>
void calcCombTable(vector<vector<T>>& table, int maxN, int maxR, int mod = 1) {
    for (int n = 1; n <= maxN; ++n) {
        vector<T> row;
        for (int r = 0; r <= n; ++r) {
            if (r == 0 || r == n) {
                row.push_back(static_cast<T>(1));
            }
            else {
                row.push_back((table[n-2][r-1] + table[n-2][r]) % mod);
            }
        }
        table.push_back(row);
    }
}

int main() {
    int R, C, X, Y, D, L;

    cin >> R >> C >> X >> Y >> D >> L;

    // arrangement of desk and rack ({}_{X*Y}C_{D})
    vector<vector<long long int>> comb;
    calcCombTable(comb, X*Y, D, MOD);
    cout << ((comb[X*Y-1][D] * (X*Y - D - L)) % MOD * ((R-X+1)*(C-Y+1) % MOD)) % MOD << endl;

    return 0;
}
