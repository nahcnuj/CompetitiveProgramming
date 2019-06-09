#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;
const int MOD = 1000000007;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<int> A(N+10, 0), dp(N+1, 0);
    for (int i = 0, a; i < M; ++i) {
        cin >> a;
        A[a] = 1;
    }

    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        if (A[i]) continue;
        
        if (!A[i-1]) {
            dp[i] += dp[i-1];
            dp[i] %= MOD;
        }
        if (i > 1 && !A[i-2]) {
            dp[i] += dp[i-2];
            dp[i] %= MOD;
        }
    }

    cout << dp[N] << endl;

    return 0;
}
