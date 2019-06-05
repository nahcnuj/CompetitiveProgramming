#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int A, B;
    cin >> A >> B;
    
    cout << (A >= 13 ? B : A >= 6 ? B/2 : 0) << endl;

    return 0;
}
