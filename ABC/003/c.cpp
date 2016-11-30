#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

const int INF = 1e8;

int main() {
    int N, K;
    vector<int> R;

    cin >> N >> K;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        R.push_back(x);
    }
    sort(begin(R), end(R));

    double r = 0;
    for (int k = 0; k < K; ++k) {
        int i = N - K + k;
        if (r > R[i]) break;

        r = (r + R[i]) / 2.0;
    }

    printf("%.8f\n", r);

    return 0;
}
