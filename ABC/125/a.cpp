#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int A, B, T;
    cin >> A >> B >> T;
    
    cout << T / A * B << endl;

    return 0;
}
