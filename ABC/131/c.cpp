#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;
const int MOD = 1000000007;

using namespace std;

ll gcd(ll a, ll b) {
    while (a > 0) {
        ll t = a;
        a = b % a;
        b = t;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(false);

    ll A, B, C, D;
    cin >> A >> B >> C >> D;

    ll lcm = C / gcd(C, D) * D;

    cout << B - (B/C + B/D - B/lcm) - ((A-1) - ((A-1)/C + (A-1)/D - (A-1)/lcm) ) << endl;

    return 0;
}
