#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = (ll)1e11;

int main() {
    ll N, x;
    vector<ll> a;

    cin >> N >> x;
    ll mina = INF, ii;
    ll ans = 0;
    for (int i = 0, t; i < N; ++i) {
        cin >> t;
        if (t > x) {
            ans += t - x;
            t = x;
        }
        a.push_back(t);
        if (mina > t) {
            mina = t;
            ii = i;
        }
    }

    
    for (ll d = 0; 0 < ii - d || ii + d < N - 1; ++d) {
        ll l = ii - d, r = ii + d;
        if (0 < l) {
            ll le = max(0ll, a[l] + a[l - 1] - x);
            a[l - 1] -= le;
            ans += le;
        }
        if (r < N - 1) {
            ll re = max(0ll, a[r + 1] + a[r] - x);
            a[r + 1] -= re;
            ans += re;
        }
    }
    cout << ans << endl;

    return 0;
}
