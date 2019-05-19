#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e11;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string S;
    cin >> S;

    bool canYYMM = (S[2] == '0' && S[3] > '0') || (S[2] == '1' && S[3] <= '2');
    bool canMMYY = (S[0] == '0' && S[1] > '0') || (S[0] == '1' && S[1] <= '2');

    cout << (
        canYYMM && canMMYY ? "AMBIGUOUS"
        : canYYMM ? "YYMM"
        : canMMYY ? "MMYY"
        : "NA"
    ) << endl;

    return 0;
}
