#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    ios::sync_with_stdio(false);
    ll n, X;
    cin >> n >> X;
    int ans = 0;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        ans += ((X >> i) & 1 ? a : 0);
    }
    cout << ans << endl;
    return 0;
}
