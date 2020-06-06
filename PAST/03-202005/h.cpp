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

int dx[] = {1, 0, -1, 1, -1,  0};
int dy[] = {1, 1,  1, 0,  0, -1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N,L;
    cin >> N>>L;

    vector<int> X(N+1, 1000000000);
    for (int i = 0; i < N; ++i) cin >> X[i];

    int T1,T2,T3;
    cin >>T1>>T2>>T3;

    vector<int> t(L+10);
    for (int x = 1, j = 0; x <= L+4; ++x) {
        int penalty = x == X[j] ? (++j, T3) : 0;
        int a = t[x-1] + T1 + penalty;
        int b = 1000000000, c = 1000000000;
        if (x >= 2) {
            b = t[x-2] + T1 + T2 + penalty;
        }
        if (x >= 4) {
            c = t[x-4] + T1 + 3 * T2 + penalty;
        }
        t[x] = min({a, b, c});
        if (x > L) {
            if (t[x] == b && x - L <= 1) {
                t[L] = min(t[L], b - (T1 + T2) / 2 - penalty);
            } else if (t[x] == c && x - L <= 3) {
                t[L] = min(t[L], c - T1 / 2 - T2 / 2 - (x - L - 1) * T2 - penalty);
            }
        }
    }

    cout << t[L] << endl;

    return 0;
}
