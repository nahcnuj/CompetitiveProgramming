#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = (ll)1e11;

int main() {
    string s;
    cin >> s;

    cout << (s == "a" || s == "e" || s == "i" || s == "o" || s == "u" ? "vowel" : "consonant") << endl;

    return 0;
}
