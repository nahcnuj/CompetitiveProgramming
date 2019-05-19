#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;


int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    ll n = 1, all = N, a = 0;
    while (n < K) {
        n *= 2;
        all *= 2;
        ++a;
    }

    ll cnt = 0;
    for (int i = 1; i <= N; ++i) {
        int j = i, k = 0;
        double t = 1.0 / N;
        while (j < K) {
            j *= 2;
            t /= 2.0;
            ++k;
        }
        ll x = 1;
        for (int j = 0; j < a - k; ++j) x *= 2;
        cnt += x;
    }

    printf("%.20lf\n", (double)cnt/all);

    return 0;
}
