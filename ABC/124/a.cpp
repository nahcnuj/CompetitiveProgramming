#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int a[2];
    cin >> a[0] >> a[1];
    
    if (a[0] > a[1]) {
        cout << a[0] * 2 - 1 << endl;
    } else if (a[0] < a[1]) {
        cout << a[1] * 2 - 1 << endl;
    } else {
        cout << a[0] * 2 << endl;
    }

    return 0;
}
