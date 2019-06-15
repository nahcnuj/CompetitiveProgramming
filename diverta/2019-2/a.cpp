#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;
    if (K == 1) {
        cout << 0 << endl;
        return 0;
    }
    cout << max((N+K-1)/K - N/K, (N-K+1) - 1) << endl;

    return 0;
}
