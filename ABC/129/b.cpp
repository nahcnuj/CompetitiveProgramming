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

    vector<int> S;
    for (int i = 0, s = 0, w; i < N; ++i) {
        cin >> w;
        S.push_back(s += w);
    }

    int ans = 1<<30;
    for (int i = 0; i < N-1; ++i) {
        int d = S[i] - (S[N-1] - S[i]);
        if (d < 0) d *= -1;
        ans = min(ans, d);
    }

    cout << ans << endl;

    return 0;
}
