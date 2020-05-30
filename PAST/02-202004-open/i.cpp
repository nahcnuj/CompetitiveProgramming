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

    int n;
    cin >> n;
    
    vector<int> offset;
    offset.push_back(0);
    for (int i = 0, o = 0; i < n - 1; ++i) {
        o += 1 << (n - i);
        offset.push_back(o);
    }


    vector<int> as(1<<n), last(1<<n);
    vector<int> t((1 << (n + 1)) - 2);
    for (int i = 0; i < (1 << n); ++i) {
        cin >> as[i];
        t[i] = i;
    }

    for (int stage = 1; stage < n; ++stage) {
        cerr << "# stage: "<<  stage << " " << endl;
        for (int i = 0; i < (1 << (n - stage)); ++i) {
            int p = offset[stage - 1] + 2 * i, p1 = t[p], p2 = t[p + 1];
            t[offset[stage] + i] = as[p1] > as[p2] ? p1 : p2;
        }
    }

    for (int i = 0; i < (1 << n); ++i) {
        int oi = i, s = 0;
        while (t[oi] == i && s < n) {
            oi = offset[s+1] + (oi - offset[s]) / 2;
            ++s;
        }
        cout << s << endl;
    }

    return 0;
}
