#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

template<typename T>
constexpr T gcd(T a, T b) { return (b == 0 ? a : gcd(b, a%b)); }

template<typename T>
constexpr T lcm(T a, T b) { return a / gcd(a,b) * b; }

int main() {
    ll n, m;
    cin >> n >> m;
    if (4 * n - m < 0) {
        cout << "-1 -1 -1" << endl;
        return 0;
    }
    for (ll a = 3 * n - m; a <= (4 * n - m) / 2; ++a) {
        ll b = 4 * n - m - 2 * a;
        ll c = a - 3 * n + m;
        if (a >= 0 && b >= 0 && c >= 0) {
            cout << a << " " << b << " " << c << endl;
            return 0;
        }
    }
    cout << "-1 -1 -1" << endl;
    return 0;
}
