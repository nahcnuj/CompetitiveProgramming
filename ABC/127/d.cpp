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

    vector<int> A(N);
    vector<Pii> BC(M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &(BC[i].second), &(BC[i].first));
    }

    sort(A.begin(), A.end());

    sort(BC.rbegin(), BC.rend());

    ll sum = 0;
    int cnt = 0;

    for (int i = 0; i < M && cnt < N; ++i) {
        int replaceable = distance(A.begin(), lower_bound(A.begin(), A.end(), BC[i].first)) - cnt;
        if (replaceable <= 0) break;
        int replace = min(replaceable, BC[i].second);
        sum += (ll)BC[i].first * replace;
        cnt += replace;
    }

    for (int i = cnt; i < N; ++i) {
        sum += (ll)A[i];
    }

    cout << sum << endl;

    return 0;
}
