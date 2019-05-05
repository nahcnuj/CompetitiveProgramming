#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, M = 0;
    cin >> N;

    int s = 0, mul = 1;
    for (int i = 0; i < N; ++i) {
        char c;
        int a;
        cin >> c >> a;
        if (c == '+') {
            s += a;
        } else if (c == '*' && a > 0) {
            mul *= a;
        }
    }

    cout << s * mul << endl;    

    return 0;
}
