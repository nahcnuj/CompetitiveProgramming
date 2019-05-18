#include <bits/stdc++.h>
using namespace std;

using Int = int64_t;

const Int INF = 1e8;
const Int MOD = 1e9 + 7;

template<int N>
struct Comb {
    Int array[N+1][N+1] = {{1}};

    constexpr Comb() {
        for (int n = 1; n <= N; ++n) {
            array[n][0] = array[n][n] = 1;
            for (int r = 1; r < n; ++r) {
                array[n][r] = (array[n-1][r-1] + array[n-1][r]) % MOD;
            }
        }
    }

    constexpr auto operator()(Int n, Int r) const {
        return array[n][r];
    }
};

constexpr auto comb = Comb<30*30>();

int main() {
    int R, C, X, Y, D, L;

    cin >> R >> C >> Y >> X >> D >> L;

    Int ans = 0;

    for (int x = 0; x <= 2; ++x) {
        if (X - x < 0) break;
        for (int y = 0; y <= 2; ++y) {
            if (Y - y < 0) break;

            // 左右端・上下端をそれぞれ x 辺・y 辺使わない場合の置き方
            auto t = comb((X-x)*(Y-y), D+L) * comb(D+L, D) % MOD;
            // 1辺使わない場合は，どっちの辺を選ぶかで2通り
            t = t * ((x == 1) + 1) * ((y == 1) + 1) % MOD;

            // 包除原理
            if ((x + y) % 2 == 0) {
                ans += t;
            } else {
                ans -= t;
            }
            
            ans = (ans + MOD) % MOD;
        }
    }
    ans = ans * (C - X + 1) % MOD * (R - Y + 1) % MOD;

    cout << ans << endl;

    return 0;
}
