#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = (ll)1e11;

int main() {
    string s;
    cin >> s;

    cout << ( ((s.length() % 2 == 0) ^ (s.front() == s.back())) ? "Second" : "First" ) << endl;

    return 0;
}
