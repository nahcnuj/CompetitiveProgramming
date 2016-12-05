#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

int main() {
    ios::sync_with_stdio(false);

    int N;
    map<string, int> t;
    cin >> N;
    int m = 0;
    string ans;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        if (t.count(s)) {
            t[s]++;
        }
        else {
            t[s] = 1;
        }

        if (m < t[s]) {
            m = t[s];
            ans = s;
        }
    }
    cout << ans << endl;
    return 0;
}
