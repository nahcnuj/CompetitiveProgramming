#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

ll a[1000000];
int main() {
    int n, x;
    ll ans = 0;
    scanf("%d %d", &n, &x);
    for (int i = 0, t; i < n; ++i) {
        scanf("%d", &t);
        ans += a[t];
        ++a[t^x];
    }
    cout << ans << endl;
    return 0;
}
