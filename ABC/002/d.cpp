#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

int main() {
    int N, M;
    
    cin >> N >> M;

    bool rel[12][12] = {};
    for (int i = 0, x, y; i < M; i++) {
        cin >> x >> y;
        rel[x-1][y-1] = rel[y-1][x-1] = true;
    }

    int ans = 0;
    for (int S = 1; S < 1 << N; S++) {
        bool ok = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (S >> i & S >> j & 1 && !rel[i][j]) {
                    ok = false;
                }
            }
        }

        if (ok) {
            ans = max(ans, (int) bitset<32>(S).count());
        }
    }

    cout << ans << endl;

    return 0;
}
