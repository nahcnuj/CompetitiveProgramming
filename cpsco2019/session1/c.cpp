#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int N, K;
vector<ll> A(32), C{1, 5, 10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000ll, 500000000ll, 1000000000ll, 5000000000ll};

ll ans = 1e15;

void solve(int idx, vector<int> v) {
    cerr << idx << endl;
    if (v.size() == K) {
        ll sum = 0, coin = 0;
        for (auto i : v) sum += A[i];
        for (int i = 19; i >= 0 && sum > 0; --i) {
            ll c = sum / C[i];
            coin += c;
            sum -= c * C[i];
        }
        ans = min(ans, coin);
        return;
    }

    for (int i = idx; i < N; ++i) {
        vector<int> v2(v);
        v2.push_back(i);
        solve(i + 1, v2);
    }
}

int main() {
    ios::sync_with_stdio(false);

    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> A[i];

    solve(0, vector<int>());
    cout << ans << endl;

    return 0;
}
