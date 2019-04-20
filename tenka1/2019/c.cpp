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
    string s, t;
    cin >> t;
    s = "." + t;

    vector<int> b;  // black in [0..i]
    for (int i = 0, bn = 0; i <= n; ++i) {
        if (s[i] == '#') {
            ++bn;
        }
        b.push_back(bn);
    }

    if (b[n] == n) {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> a;  // [0..i]: .  [i+1..n-1]: #
    for (int i = 0; i <= n; ++i) {
        a.push_back(b[i] + n - i - b[n] + b[i]);
    }
    sort(begin(a), end(a));
    cout << a[0] << endl;    

    return 0;
}
