#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <functional>
#include <queue>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

using pint = pair<int,int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N;
    cin >> N;

    vector<string> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    string S(N, '.');
    for (int i = 0; i <= N/2; ++i) {
        if (N % 2 == 1 && i == N/2) {
            S[i] = A[i][0];
        } else {
            for (int j = 0; j < N; ++j) {
                auto&& c = A[i][j];
                for (int k = 0; k < N; ++k) {
                    if (c == A[N-1-i][k]) {
                        S[i] = S[N-1-i] = c;
                        goto nextchar;
                    }
                }
            }
            cout << -1 << endl;
            return 0;
        }
        nextchar:;
    }

    cout << S << endl;

    return 0;
}
