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

    int N,M;
    cin >> N >> M;

    vector<int> eaten(N, 0);
    for (int i = 0; i < M; ++i) {
        int a;
        cin >> a;
        auto&& itr = upper_bound(eaten.rbegin(), eaten.rend(), a);
        auto x = distance(itr, eaten.rend());
        //cerr << a << " " << x << " " << (x > 0 ? eaten[x-1] : -1) << "," << eaten[x] << "," << eaten[x+1] << endl;
        while (x > 0 && eaten[x] == a) {
            ++x;
        }
        //cerr << a << " " << x << " " << (x > 0 ? eaten[x-1] : -1) << "," << eaten[x] << "," << eaten[x+1] << endl;
        eaten[x] = a;
        cout << (x < N ? x + 1 : -1) << endl;
    }

    return 0;
}
