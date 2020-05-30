#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <functional>
#include <queue>
#include <sstream>
#include <cstdio>
#include <map>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);


    int q;
    scanf("%d", &q);

    int p = 0;
    vector<pair<char, int>> ss;
    vector<long long int> cnt(30, 0);
    while (q--) {
        int t;
        scanf("%d ", &t);

        if (t == 1) {
            char c;
            int x;
            scanf("%c %d", &c, &x);
            ss.emplace_back(c, x);
        } else {
            int d;
            scanf("%d", &d);
            auto itr = ss.begin();
            for (; !ss.empty() && d > 0;) {
                int removelen = min(itr->second, d);
                cnt[itr->first - 'a'] += removelen;
                if ((itr->second -= removelen) <= 0) {
                    itr = ss.erase(itr);
                }
                d -= removelen;
            }
            long long int m = 0;
            for (int i = 0; i < 30; ++i) {
                long long int x = cnt[i];
                m += x * x;
                cnt[i] = 0;
            }
            printf("%lld\n", m);
        }
    }

    return 0;
}
