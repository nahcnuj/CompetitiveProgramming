#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A;
    for (int i = 0, a; i < N; ++i) {
        cin >> a;
        A.push_back(a);
    }

    ll dp[100000][2] = {};
    dp[0][0] = A[0] + A[1];
    dp[0][1] = -dp[0][0];

    for (int i = 1; i < N - 1; ++i) {
        dp[i][0] = max(dp[i-1][0] + A[i+1], dp[i-1][1] + A[i+1]);
        dp[i][1] = max(dp[i-1][0] + -2 * A[i] - A[i+1], dp[i-1][1] +2 * A[i] - A[i+1]);
    }

    cout << max(dp[N-2][0], dp[N-2][1]) << endl;

    return 0;
}
