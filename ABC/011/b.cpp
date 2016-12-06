#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

inline bool isSmallAlpha(char a) {
    return ('a' <= a && a <= 'z');
} 

int main() {
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    cout << (isSmallAlpha(S[0]) ? (char)('A' + (S[0] - 'a')) : S[0]);
    for (int i = 1; i < S.length(); ++i) {
        cout << (isSmallAlpha(S[i]) ? S[i] : (char)('a' + (S[i] - 'A')));
    }
    cout << endl;
    return 0;
}
