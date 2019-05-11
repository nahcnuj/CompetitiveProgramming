#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int R, G, B, N;
    cin >> R >> G >> B >> N;

    int ans = 0;
    for (int r = 0; r <= N / R + 1; ++r) {
        for (int g = 0; g <= (N - r * R) / G + 1; ++g) {
            if (r * R + g * G > N) break;
            if ((N - r * R - g * G) % B == 0) ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}
