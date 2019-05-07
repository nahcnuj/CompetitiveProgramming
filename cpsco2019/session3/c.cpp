#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int a[1000000+10];

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int s, t;
        cin >> s >> t;
        a[s]++;
        a[t]--;
    }
    int x = 0;
    for (int i = 1; i <= 1000000; ++i) {
        a[i] = (x += a[i]);
    }
    int ans = 0;
    for (int i = 0; i <= 1000000; ++i) {
        if (a[i] == 0 && a[i+1] > 0) ++ans;
    }

    cout << ans << endl;

    return 0;
}
