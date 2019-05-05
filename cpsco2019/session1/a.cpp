#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, A;
    cin >> N >> A;

    cout << (A + 2) / 3 << " " << min(N/3, A) << endl;    

    return 0;
}
