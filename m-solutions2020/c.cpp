#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    vector<long long int> A(N);
    for (auto& a : A) {
        cin >> a;
    }
    
    for (int t = 1; t <= N; ++t) {
        if (t > K) {
            cout << (A[t-1] > A[t - K - 1] ? "Yes" : "No") << endl;
        }
    }

    return 0;
}
