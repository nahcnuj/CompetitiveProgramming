#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int gcd(int n, int m) {
    return n == 0 ? m
         : m == 0 ? n
         : n < m ? gcd(m, n)
         : gcd(m, n%m);
}

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A;
    for (int i = 0, a; i < N; ++i) {
        cin >> a;
        A.push_back(a);
    }

    // The finding number is the maximum GCD of a[] excluding a[i] (0 <= i < N)
    //  = GCD(GCD(a[0..i-1]), GCD(a[i+1..N-1]))

    // a[0] a[1] ... a[i-1] a[i] a[i+1] ... a[N-2] a[N-1]
    // ^^^^^^^^^^^^^^^^^^^^      ^^^^^^^^^^^^^^^^^^^^^^^^
    //       lgcd[i]                     rgcd[i]
    int lgcd[100000 + 1] = {}, rgcd[100000 + 1] = {};
    for (int i = 0; i < N; ++i) {
        lgcd[i + 1] = gcd(lgcd[i], A[i]);
        rgcd[N - i - 1] = gcd(A[N - i], rgcd[N - i]);
    }

    int maxGcd = 1;
    for (int i = 0; i < N; ++i) {
        maxGcd = max(maxGcd, gcd(lgcd[i], rgcd[i]));
    }
    cout << maxGcd << endl;

    return 0;
}
