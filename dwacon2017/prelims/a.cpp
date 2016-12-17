#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, a, b;
    cin >> n >> a >> b;

    cout << max(0, a + b - n) << endl;

    return 0;
}
