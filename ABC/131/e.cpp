#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    int maxK = (N-1)*(N-2)/2;
    if (K > maxK) {
        cout << -1 << endl;
        return 0;
    }

    cout << N - 1 + maxK - K << endl;
    for (int i = 2; i <= N; ++i) {
        cout << "1 " << i << endl;
    }
    
    int k = 0;
    for (int i = 2; i < N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (k++ >= maxK - K) return 0;
            cout << i << " " << j << endl;
        }
    }

    return 0;
}
