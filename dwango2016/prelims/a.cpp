#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

template<typename T>
struct UnionFind {
    std::vector<T> parent;
    std::vector<T> rank;
    UnionFind(T n) : parent(n), rank(n,0) { std::iota(parent.begin(), parent.end(), 0); }

    T find(T x) { return (parent[x] == x ? x : (parent[x] = find(parent[x]))); }

    void unite(T x, T y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) parent[x] = y;
        else {
            parent[y] = x;
            if (rank[x] == rank[y]) ++rank[x];
        }
    }
    
    bool inSame(T x, T y) { return find(x) == find(y); }
};

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    cout << N / 25 << endl;

    return 0;
}
