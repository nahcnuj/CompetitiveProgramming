#include <bits/stdc++.h>
using namespace std;

const int INF = 1<<30;

int main() {
    int R, G, B;
    cin >> R >> G >> B;

    int ans = INF;

    for (int lG = -1000; lG <= 1000; ++lG) {
        int lR = min(-100 - R/2, lG - R);
        int lB = max( 100 - B/2, lG + G);
        int s = 0;
        for (int i = lR; i < lR + R; ++i) s += abs(-100 - i);
        for (int i = lG; i < lG + G; ++i) s += abs(   0 - i);
        for (int i = lB; i < lB + B; ++i) s += abs( 100 - i);
        ans = min(ans, s);
    }

    cout << ans << endl;

    return 0;
}
