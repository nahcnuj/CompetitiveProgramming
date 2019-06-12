#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    bool lamp[10+1][10+1] = {};
    for (int i = 1, k; i <= M; ++i) {
        cin >> k;
        for (int j = 1, s; j <= k; ++j) {
            cin >> s;
            lamp[i][s] = 1;
        }
    }

    int cond[10+1] = {};
    for (int i = 1; i <= M; ++i) {
        cin >> cond[i];
    }

    int ans = 0;
    for (unsigned s = 0; s < (1 << N); ++s) {
        int on = 0;
        for (int i = 1; i <= M; ++i) {
            int p = 0;
            for (int j = 1; j <= N; ++j) {
                if (((s >> (j-1)) & 1) && lamp[i][j]) {
                    ++p;
                }
            }
            if (p % 2 == cond[i]) {
                ++on;
            }
        }
        if (on == M) {
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}
