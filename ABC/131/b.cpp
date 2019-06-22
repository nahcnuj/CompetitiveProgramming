#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, L;
    cin >> N >> L;

    if (L <= 0 && L + N - 1 > 0 || L < 0 && L + N - 1 >= 0) {
        cout << L*N + N*(N-1)/2 << endl;
    } else {
        if (abs(L) < abs(L+N-1)) {
            cout << L*N + N*(N-1)/2 - L << endl;
        } else {
            cout << L*N + N*(N-1)/2 - L - N + 1<< endl;
        }
    }


    return 0;
}
