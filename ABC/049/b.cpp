#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = (ll)1e11;

int main() {
    int h, w;
    vector<string> s;
    cin >> h >> w;
    for (int i = 0; i < h; ++i) {
        string t;
        cin >> t;
        s.push_back(t);
    }

    for (int i = 0; i < h; ++i) {
        cout << s[i] << endl;
        cout << s[i] << endl;
    }

    return 0;
}
