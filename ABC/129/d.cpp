#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;

    vector<string> S(H);
    for (int r = 0; r < H; ++r) {
        cin >> S[r];
    }

    vector<vector<int>> light(H, vector<int>(W));
    for (int r = 0; r < H; ++r) {
        int prevWall = -1, d = 0;
        for (int c = 0; c < W; ++c) {
            if (S[r][c] == '#') {
                for (int i = prevWall + 1; i < c; ++i) {
                    light[r][i] += d;
                }
                prevWall = c;
                d = 0;
            } else {
                ++d;
            }
        }
        for (int i = prevWall + 1; i < W; ++i) {
            light[r][i] += d;
        }
    }

    for (int c = 0; c < W; ++c) {
        int prevWall = -1, d = 0;
        for (int r = 0; r < H; ++r) {
            if (S[r][c] == '#') {
                for (int i = prevWall + 1; i < r; ++i) {
                    light[i][c] += d - 1;
                }
                prevWall = r;
                d = 0;
            } else {
                ++d;
            }
        }
        for (int i = prevWall + 1; i < H; ++i) {
            light[i][c] += d - 1;
        }
    }

    int ans = 0;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            ans = max(ans, light[r][c]);
        }
    }

    cout << ans << endl;

    return 0;
}
