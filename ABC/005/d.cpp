#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

template<typename T>
using VV = std::vector<std::vector<T>>;

using namespace std;

template<int N>
struct Divisor {
    int divs[N+1][N+1] = {};

    constexpr Divisor() {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1, k = 0; j * j <= i; ++j) {
                if (i % j == 0) {
                    divs[i][k++] = j;
                    divs[i][k++] = i/j;
                }
            }
        }
    }
};

constexpr auto DIVS = Divisor<50*50>();

const ll INF = (ll)1e16;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    VV<int> D(N + 1, vector<int>(N + 1, 0)), sums = D;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> D[j][i];
            sums[j+1][i+1] = sums[j+1][i] + sums[j][i+1] - sums[j][i] + D[j][i];
        }
    }
    int Q;
    cin >> Q;
    vector<int> ans(N*N + 1, 0);
    for (int k = 1; k <= N*N; ++k) {
        for (int j = 0; DIVS.divs[k][j] > 0; ++j) {
            auto c = DIVS.divs[k][j], r = k/c;
            for (int y = r; y <= N; ++y) {
                for (int x = c; x <= N; ++x) {
                    ans[k] = max(ans[k], sums[x][y] - sums[x-c][y] - sums[x][y-r] + sums[x-c][y-r]);
                }
            }
        }
    }
    for (int i = 0; i < Q; ++i) {
        int P;
        cin >> P;
        int ret = 0;
        for (int i = 1; i <= P; ++i) {
            ret = max(ret, ans[i]);
        }
        cout << ret << endl;
    }

    return 0;
}
