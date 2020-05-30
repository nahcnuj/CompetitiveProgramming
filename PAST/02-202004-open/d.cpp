#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    unordered_set<string> ps;

    string s;
    cin >> s;
    for (int i = 1; i <= min((int)s.length(), 3); ++i) {
        ps.insert(string(i, '.'));
    }

    for (int l = 1; l <= min((int)s.length(), 3); ++l) {
        for (int i = 0; i <= s.length() - l; ++i) {
            string subs = s.substr(i, l);
            ps.insert(subs);
            for (unsigned int mask = 1; mask < (1<<l); ++mask) {
                string t(subs);
                for (int j = 0; j < l; j++) {
                    if ((mask >> j) & 1) {
                        t[j] = '.';
                    }
                }
                ps.insert(t);
            }
        }
    }

    cout << ps.size() << endl;

    return 0;
}
