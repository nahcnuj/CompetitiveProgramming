#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    int ans = 0, lastA = 0, firstB = 0, both = 0;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        char pr = '_';
        for (int j = 0; j < s.length(); ++j) {
            if (pr == 'A' && s[j] == 'B') {
                ++ans;
            }
            pr = s[j];
        }
        if (s[0] == 'B' && s[s.length() - 1] == 'A') {
            ++both;
        } else if (s[s.length() - 1] == 'A') {
            ++lastA;
        } else if (s[0] == 'B') {
            ++firstB;
        }
    }

    ans += max(0, both - 1);
    if (both > 0) {
        if (lastA > 0) {
            ++ans;
            --lastA;
        }
        if (firstB > 0) {
            ++ans;
            --firstB;
        }
    }
    ans += min(lastA, firstB);

    cout << ans << endl;

    return 0;
}
