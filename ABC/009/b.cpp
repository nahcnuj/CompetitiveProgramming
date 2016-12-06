#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    ios::sync_with_stdio(false);

    int N, m = -1, ans = -1;
    cin >> N;
    for (int i = 0, a; i < N; ++i) {
        cin >> a;
        if (m < a) {
            if (ans != m) ans = m;
            m = a;
        }
        else if (ans < a) {
            if (m != a) ans = a;
        }
    }
    cout << ans << endl;
    return 0;
}
