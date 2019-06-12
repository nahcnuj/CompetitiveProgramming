#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    struct T {
        int no;
        string s;
        int p;
        T(int no_, string s_, int p_) : no(no_), s(s_), p(p_) {}
    };
    auto cmp = [](const T& l, const T& r) { return l.s < r.s || l.s == r.s && l.p > r.p; };
    set<T, decltype(cmp)> S(cmp);

    string s;
    int p;
    for (int i = 0; i < N; ++i) {
        cin >> s >> p;
        S.emplace(i+1, s, p);
    }

    for (auto x : S) {
        cout << x.no << endl;
    }

    return 0;
}
