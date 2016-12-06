#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    ios::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    cout << (b - (a%b))%b << endl;
    return 0;
}
