#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int x, y, z;
    ll K;
    cin >> x >> y >> z >> K;
    vector<ll> a, b, c;
    for (int i = 0; i < x; ++i) {
        ll t;
        cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < y; ++i) {
        ll t;
        cin >> t;
        b.push_back(t);
    }
    for (int i = 0; i < z; ++i) {
        ll t;
        cin >> t;
        c.push_back(t);
    }

    vector<ll> ab;
    for (auto s : a) {
        for (auto t : b) {
            ab.push_back(s + t);
        }
    }
    sort(begin(ab), end(ab), greater<ll>());

    vector<ll> abc;
    for (int i = 0; i < min((ll)ab.size(), K); ++i) {
        for (auto u : c) {
            abc.push_back(ab[i] + u);
        }
    }
    sort(begin(abc), end(abc), greater<ll>());
    
    for (int i = 0; i < K; ++i) {
        cout << abc[i] << endl;
    }

    return 0;
}
