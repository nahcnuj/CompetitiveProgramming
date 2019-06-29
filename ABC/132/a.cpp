#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    
    map<char, int> cnt;
    for (char c : S) {
        ++cnt[c];
    }
    if (cnt.size() > 2) {
        cout << "No" << endl;
        return 0;
    }
    for (auto p : cnt) {
        if (p.second != 2) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
