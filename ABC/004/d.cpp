#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

const int INF = 1e8;

// x個の同色のマーブルを左右一方の側で1個以下にする
int f(int x) {
    if (x <= 0) return 0;

    return x * (x-1) / 2;
}

// x個の同色のマーブルを左右両方で1個以下にする
int g(int x) {
    return x/2 + f(x/2) + f((x+1)/2);
}

int main() {
    int R, G, B;
    cin >> R >> G >> B;

    if (G <= 199) {
        // all green marbles go in a range of [-99, 99]
        cout << g(R) + g(G) + g(B) << endl;
    }
    else {
        int ans = INF;
        for (int k = 0; k <= G; ++k) {
            int rt, gt, bt;

            int rightR = 99 - (G - k);
            if (rightR > 0) {
                rt = rightR + f(rightR) + f(R - rightR);
            }
            else {
                rt = (G - 99 - k) * R + f(R);
            }

            gt = f(k) + (G - k) + f(G - k);

            int leftB = 99 - k;
            if (leftB > 0) {
                bt = leftB + f(leftB) + f(B - leftB);
            }
            else {
                bt = (k - 100) * B + f(B);
            }
            ans = min(ans, rt + gt + bt);
        }
        cout << ans << endl;
    }

    return 0;
}
