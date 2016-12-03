#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;


int main() {
    int R, C;
    cin >> R >> C;

    int ans = 0;
    for (int y = C; y <= R; y+=C) {
        for (int x = C; x <= R; x+=C) {
            if (x*x+y*y <= R*R) ++ans;
        }
    }

    cout << 4 * ans << endl;
    return 0;
}
