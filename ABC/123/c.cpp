#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    ll a[5], m = INF;
    for (int i = 0; i < 5; ++i) {
        cin >> a[i];
        m = min(m, a[i]);
    }

    cout << (n + m - 1) / m + 4 << endl;

    return 0;
}
