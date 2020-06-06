#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <functional>
#include <queue>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

using pint = pair<int,int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N,M,Q;
    cin >> N>>M>>Q;

    vector<vector<int>> neighbor(N+1);
    for (int i = 0; i < M; ++i) {
        int u,v;
        cin >> u>>v;
        neighbor[u].push_back(v);
        neighbor[v].push_back(u);
    }

    vector<int> color(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> color[i];
    }

    for (int q = 0; q < Q; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            cout << color[x] << endl;
            for (auto&& y : neighbor[x]) {
                color[y] = color[x];
            }
        } else {
            int x,y;
            cin >> x >> y;
            cout << color[x] << endl;
            color[x] = y;
        }
    }

    return 0;
}
