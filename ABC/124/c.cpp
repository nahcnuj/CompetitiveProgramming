#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string s;
    cin >> s;

    int prev = s[0] - '0', ans = 0;
    for (int i = 1; i < s.length(); ++i) {
        prev = 1 - prev;
        if (s[i] == s[i-1]) {
            ++ans;
            s[i] = '0' + prev;
        }
    }

    cout << ans << endl;

    return 0;
}
