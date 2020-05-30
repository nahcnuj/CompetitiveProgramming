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

int calc(const pint& a, const pint& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);


    int n, m;
    cin >> n >> m;

    vector<vector<pint>> points(11);    // 0=S, 1, ..., 9, 10=G
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            int idx = c == 'S' ? 0
                    : c == 'G' ? 10
                    : (c - '0');
            points[idx].emplace_back(i, j);
        }
    }

    vector<map<pint, int>> dd(11);
    dd[0].emplace(points[0][0], 0);

    for (int next = 1; next <= 10; ++next) {
        //cerr << "--------------" << next << endl;
        auto&& now = dd[next-1];
        auto&& dist = points[next];
        if (dist.empty()) {
            cout << -1 << endl;
            return 0;
        }
        for (auto&& distp : dist) {
            //cerr << "# " << distp.first << "," << distp.second << "  " << endl;
            int mind = 100000000;
            pint minp;
            for (auto&& p : now) {
                int d = p.second + calc(p.first, distp);
                //cerr << "## <- " << p.first.first << "," << p.first.second << "  " << d << endl;
                if (mind > d) {
                    mind = d;
                    minp = p.first;
                }
            }
            dd[next].emplace(distp, mind);
            //cerr << "## " << next << "   " << minp.first << "," << minp.second << "  " << mind << endl;
        }
    }

    for (auto&& x : dd[10]) {
        //cerr << x.first.first << "," << x.first.second << "  " << x.second << endl;
    }
    //cerr << points[10][0].first << points[10][0].second << endl;
    cout << dd[10][points[10][0]] << endl;

    return 0;
}
