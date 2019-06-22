#include <bits/stdc++.h>

using Pii = std::pair<int, int>;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    priority_queue<pair<int, int>, vector<Pii>, greater<Pii>> q;
    for (int i = 0, a, b; i < N; ++i) {
        cin >> a >> b;
        q.emplace(b, a);
    }

    int t = 0;
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        int a = p.second, b = p.first;
        if (t + a <= b) {
            t += a;
        } else {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
