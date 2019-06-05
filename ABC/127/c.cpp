#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    int passable[100000+1] = {};
    for (int i = 0; i < M; ++i) {
        int L, R;
        cin >> L >> R;
        ++passable[L];
        --passable[R+1];
    }
    int joker = 0;
    for (int i = 1; i <= N; ++i) {
        passable[i] += passable[i-1];
        if (passable[i] == M) {
            ++joker;
        }
    }

    cout << joker << endl;

    return 0;
}
