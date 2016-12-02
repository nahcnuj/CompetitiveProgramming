#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;


int N, X;
vector<int> T, A;

// u[t]: 時刻tで食べられる物
vector<int> u[100000+1];

ll sum(int t) {
    for (int i = 0; i < t; ++i) {
        u[i].clear();
    }

    for (int i = 0; i < N; ++i) {
        // 時刻 T[i] > t で食べられなくなる物は時刻 t で食べられる
        u[min(t, T[i]) - 1].push_back(A[i]);
    }

    ll s = 0;
    priority_queue<ll> q;
    for (int i = t - 1; i >= 0; --i) {
        for (ll a : u[i]) {
            q.push(a);
        }

        // 時刻 i で食べられる物(q)のうち最大のもの(q.top())を選んで食べる
        if (!q.empty()) {
            s += q.top();
            q.pop();
        }
    }

    return s;
}

int main() {
    cin >> N >> X;
    for (int i = 0, t; i < N; ++i) {
        cin >> t;
        T.push_back(t);
    }
    for (int i = 0, a; i < N; ++i) {
        cin >> a;
        A.push_back(a);
    }

    int left = 0, right = N + 1;
    while (left + 1 < right) {
        int t = (left + right) / 2;
        if (sum(t) >= X) {
            right = t;
        }
        else {
            left = t;
        }
    }

    if (right >= N + 1) {
        cout << -1 << endl;
    }
    else {
        cout << right << endl;
    }

    return 0;
}
