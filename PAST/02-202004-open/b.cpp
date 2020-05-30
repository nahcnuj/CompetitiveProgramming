#include <iostream>
#include <string>
using namespace std;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    string s;
    cin >> s;
    int v[] = {0, 0, 0};
    for (auto&& c : s) {
        ++v[c - 'a'];
    }
    int mxi = 0;
    for (int i = 1, mx = v[0]; i < 3; ++i) {
        if (mx < v[i]) {
            mx = v[i];
            mxi = i;
        }
    }
    cout << (char)('a' + mxi) << endl;
    return 0;
}
