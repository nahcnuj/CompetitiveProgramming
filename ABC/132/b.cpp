#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }

    int ans = 0;
    for (int i = 0; i < N-2; ++i) {
        int ma = max({P[i], P[i+1], P[i+2]});
        int mi = min({P[i], P[i+1], P[i+2]});
        if (P[i+1] != ma && P[i+1] != mi) ++ans;
    }

    cout << ans << endl;

    return 0;
}
