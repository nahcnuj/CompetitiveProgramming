#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    ll k;
    
    cin >> n >> k;

    while (k != 1ll << (n-1)) {
        if (k > 1ll << (n-1)) {
            k -= 1ll << (n-1);
        }
        --n;
    }

    cout << n << endl;

    return 0;
}
