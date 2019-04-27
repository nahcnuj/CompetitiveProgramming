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

    vector<int> C, V;
    for (int i = 0, v; i < N; ++i) {
        cin >> v;
        V.push_back(v);
    }
    for (int i = 0, c; i < N; ++i) {
        cin >> c;
        C.push_back(c);
    }

    int ans = -1e8;
    for (unsigned s = 0; s < (1 << N); ++s) {
        int X = 0, Y = 0;
        for (int i = 0; i < N; ++i) {
            if ((s >> i) & 1) {
                X += V[i];
                Y += C[i];
            }
        }
        ans = max(ans, X - Y);
    }
    
    cout << ans << endl;

    return 0;
}
