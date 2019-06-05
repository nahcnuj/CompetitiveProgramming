#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    ll r, D, x;
    cin >> r >> D >> x;
    
    for (int i = 0; i < 10; ++i) {
        cout << (x = r * x - D) << endl;
    }

    return 0;
}
