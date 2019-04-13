#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    
    vector<int> h;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        h.push_back(x);
    }

    int minh = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (minh <= h[i]) {
            ++ans;
            minh = h[i];
        }
    }

    cout << ans << endl;

    return 0;
}
