#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    string S;
    cin >> N >> K >> S;
    
    cout << S.substr(0, K-1) << (char)(S[K-1] - 'A' + 'a') << S.substr(K) << endl;

    return 0;
}
