#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int a[5];
    for (int i = 0; i < 5; ++i) cin >> a[i];

    sort(a, a+5);

    int ans = 1e9;
    do {
        int t = 0;
        for (int i = 0; i < 5; ++i) {
            int r = t % 10;
            if (r > 0) {
                t += 10 - r;
            }
            t += a[i];
        }
        ans = min(ans, t);
    } while (next_permutation(a, a+5));

    cout << ans << endl;

    return 0;
}
