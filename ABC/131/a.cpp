#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    
    char prev = S[0];
    for (int i = 1; i < S.length(); ++i) {
        if (prev == S[i]) {
            cout << "Bad" << endl;
            return 0;
        }
        prev = S[i];
    }

    cout << "Good" << endl;

    return 0;
}
