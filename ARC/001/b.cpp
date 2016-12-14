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

    int d = (A > B ? A - B : B - A);

    if (d%10 >= 8) {
        cout << d/10 + 1 + (10 - d%10) << endl;
    }
    else if (d%10 >= 5) {
        cout << d/10 + d%10/5 + d%5 << endl; 
    }
    else if (d%10 >= 3) {
        cout << d/10 + d%10/5 + 1 + (5 - d%5) << endl;
    }
    else {
        cout << d/10 + d%10 << endl;
    }

    return 0;
}
