#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    int n;
    cin >> n;
    
    vector<int> c;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        c.push_back(x);
    }
    sort(c.begin(), c.end());

    ll s = 0, m = 0;
    do {
        vector<int> t(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                t[j] += (c[j] % c[i] == 0);
                t[j] %= 2;
            }
        }
        s += accumulate(t.begin(), t.end(), 0);
        ++m;
    } while(next_permutation(c.begin(), c.end()));

    printf("%.8f\n", (double)s/m);

    return 0;
}
