#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;

    vector<ll> div;
    for (ll i = 1; i * i <= N; ++i) {
        if (N % i > 0) continue;
        div.push_back(i);
        if (i * i != N) div.push_back(N / i);
    }
    sort(div.begin(), div.end());

    ll ans = 0;
    for (auto q : div) {
        ll m = N / q - 1;
        if (m <= 0) continue;
        if (N / m == N % m) ans += m;
    }

    cout << ans << endl;

    return 0;
}
