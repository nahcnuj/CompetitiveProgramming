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
    cin >> N >> M >> Q;

    vector<int> solvedN(M+1,0);
    bool solved[100000+1][50+1] = {};
    for (int q = 0; q < Q; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int n;
            cin >> n;
            int sum = 0;
            for (int i = 1; i <= M; ++i) { if (solved[n][i]) sum += N - solvedN[i]; }
            cout << sum << endl;
        } else {
            int n,m;
            cin >> n >> m;
            solved[n][m] = true;
            solvedN[m]++;
        }
    }

    return 0;
}
