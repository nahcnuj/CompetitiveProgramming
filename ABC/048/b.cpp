#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;


int main() {
    ll a, b, x;

    cin >> a >> b >> x;

    cout << b/x - max(0ll,(a-1))/x + (a == 0) << endl;
    
    return 0;
}
