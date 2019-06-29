#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> s(100000+1, 0);
    map<int, int> p;
    for (int i = 0, d; i < N; ++i) {
        cin >> d;
        s[d]++;
    }
    
    int ans = 0;
    for (int k = 1; k <= 100000; ++k) {
        s[k] += s[k-1];
        if (s[k] == N/2) ++ans;
    }

    cout << ans << endl;

    return 0;
}
