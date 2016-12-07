#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

struct Edge {
    int to;
    Edge(int to_) : to(to_) {}
};

template<typename T>
constexpr T gcd(T a, T b) { return (b == 0 ? a : gcd(b, a%b)); }

template<typename T>
constexpr T lcm(T a, T b) { return a / gcd(a,b) * b; }

int main() {
    int n;
    vector<Edge> e;
    scanf("%d", &n);
    for (int i = 0, t; i < n; ++i) {
        scanf("%d", &t);
        e.push_back(Edge(t-1));
    }
    bool f[100] = {};
    vector<int> visited;
    ll ans = 1;
    for (int i = 0; i < n; ++i) {
        if (f[i]) continue;
        visited.clear();
        visited.push_back(i);
        ll l = 1;
        int now = i;
        bool ok = true;
        while ((now = e[now].to) != i) {
            if (find(visited.begin(), visited.end(), now) != visited.end()) {
                ok = false;
                break;
            }
            visited.push_back(now);
            ++l;
        }
        if (ok) {
            if (l % 2 == 0) {
                l /= 2;
            }
            ans = lcm(ans, l);
            for (auto&& x : visited) {
                f[x] = true;
            }
        }
        else {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << ans << endl;
    return 0;
}
