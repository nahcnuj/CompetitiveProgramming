#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

const int INF = 1e8;

int main() {
    int N;
    cin >> N;

    int ans = 1000;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        ans = min(x, ans);
    }

    cout << ans << endl;

    return 0;
}
