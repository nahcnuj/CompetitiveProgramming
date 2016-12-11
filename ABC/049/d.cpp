#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
using Pii = pair<int, int>;
    
const ll INF = (ll)1e11;

template<typename T>
struct UnionFind {
    std::vector<T> parent;
    std::vector<T> rank;

    UnionFind(T n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    T find(T x) {
        return (parent[x] == x ? x : (parent[x] = find(parent[x])));
    }

    void unite(T x, T y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[x] < rank[y]) {
            parent[x] = y;
        }
        else{
            parent[y] = x;
            if (rank[x] == rank[y]) {
                ++rank[x];
            }
        }
    }
    
    bool inSame(T x, T y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    int n, k, l;
    cin >> n >> k >> l;

    UnionFind<int> a(n), b(n);

    for (int i = 0; i < k; ++i) {
        int p, q;
        cin >> p >> q;
        --p; --q;
        a.unite(p, q);
    }

    for (int i = 0; i < l; ++i) {
        int p, q;
        cin >> p >> q;
        --p; --q;
        b.unite(p, q);
    }

    map<Pii, int> dict;
    for (int i = 0; i < n; ++i) {
        ++dict[{a.find(i), b.find(i)}];
    }

    for (int i = 0; i < n; ++i) {
        cout << (i > 0 ? " " : "") << dict[{a.find(i), b.find(i)}];
    }
    cout << endl;
    
    return 0;
}
