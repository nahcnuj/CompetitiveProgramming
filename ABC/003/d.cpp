#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

#define Int int64_t

const Int INF = 1e8;
const Int MOD = 1e9 + 7;


// X*Y領域のうち D+L個を選ぶ C(X*Y, D+L)
//

vector<vector<Int>> calcCombTable(Int maxN, Int maxR, Int mod = 1) {
    vector<vector<Int>> comb(maxN + 1);
    for (Int n = 0; n <= maxN; ++n) {
        vector<Int> row(n + 1);
        for (Int r = 0; r <= n; ++r) {
            if (r == 0 || r == n) {
                row[r] = 1;
            }
            else {
                cerr << comb[n-1][r-1] << " " << comb[n-1][r] << endl;
                row[r] = (comb[n-1][r-1] + comb[n-1][r]) % mod;
            }
        }
        comb[n] = row;
    }
    return comb;
}

Int calc(const vector<vector<Int>>& comb, int c, int r, int x, int y, int d, int l) {
    return comb[x*y][d+l] * (c-x+1)*(r-y+1) % MOD;
}

int main() {
    int R, C, X, Y, D, L;

    cin >> R >> C >> X >> Y >> D >> L;

    // arrangement of desk and rack ({}_{X*Y}C_{D})
    vector<vector<Int>> comb = calcCombTable(R*C, D+L, MOD);
    for (auto&& r : comb) { for (auto&& x : r) cerr << x << " "; cerr << endl; }
    //cout << ((comb[X*Y][D] * (X*Y - D - L)) % MOD * ((R-X+1)*(C-Y+1) % MOD)) % MOD << endl;

    cerr << comb[R*C][D+L] << endl;
    cerr << 2 * comb[(R-1)*C][D+L] + 2 * comb[R*(C-1)][D+L] << endl;
    cerr << comb[(R-2)*C][D+L] + comb[R*(C-2)][D+L] << endl;
    cerr << 2 * comb[(R-2)*(C-1)][D+L] + 2 * comb[(R-1)*(C-2)][D+L] << endl;
    cerr << comb[(R-2)*(C-2)][D+L] << endl;

    cout << calc(comb, C, R, X, Y, D, L) 
            - ( 2 * calc(comb, C - 1, R, X, Y, D, L) + 2 * calc(comb, C, R - 1, X, Y, D, L) )
            + ( calc(comb, C - 2, R, X, Y, D, L) + calc(comb, C, R - 2, X, Y, D, L)
                + 4 * calc(comb, C - 1, R - 1, X, Y, D, L) )
            - ( 2 * calc(comb, C - 1, R - 2, X, Y, D, L) + 2 * calc(comb, C - 2, R - 1, X, Y, D, L) )
            + calc(comb, C - 2, R - 2, X, Y, D, L)
        << endl;

    return 0;
}
