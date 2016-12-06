#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    ios::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    if (b > a) swap(a,b);
    cout << min(a-b, 10+b-a) << endl;
    return 0;
}
