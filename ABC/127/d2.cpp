#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, M;
    scanf("%d %d", &N, &M);

    vector<int> A(N), B(M), C(M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &B[i], &C[i]);
    }

    sort(A.begin(), A.end());

    vector<int> index(M);
    iota(index.begin(), index.end(), 0);
    sort(index.begin(), index.end(), [&C](auto l, auto r) {
        return C[l] > C[r];
    });

    ll sum = 0;
    int cnt = 0;

    for (int j = 0; j < M && cnt < N; ++j) {
        int i = index[j];
        int replaceable = distance(A.begin(), lower_bound(A.begin(), A.end(), C[i])) - cnt;
        if (replaceable <= 0) break;
        int replace = min(replaceable, B[i]);
        sum += (ll)C[i] * replace;
        cnt += replace;
    }

    for (int i = cnt; i < N; ++i) {
        sum += (ll)A[i];
    }

    cout << sum << endl;

    return 0;
}
