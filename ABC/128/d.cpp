#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    vector<int> V(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> V[i];
    }

    int M = min(N, K);
    int ans = 0;
    for (int l = 0; l <= M; ++l) {
        for (int r = 0; l + r <= M; ++r) {
            int sum = 0;
            vector<int> x;
            for (int i = 1; i <= N; ++i) {
                if (l < i && i < N - r + 1) continue;
                x.push_back(V[i]);
                sum += V[i];
            }
            sort(x.begin(), x.end());
            for (int i = 0; i < min((int)x.size(), K - l - r) && x[i] < 0; ++i) {
                sum -= x[i];
            }
            ans = max(ans, sum);
        }
    }

    cout << ans << endl;

    return 0;
}
