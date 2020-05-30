#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int dy[] = {-1, 0, 1};

string conv(const vector<string>& ss, int i) {
    string r(ss[i]);
    for (int j = 1; j < 2 * (int)(ss.size()) - 2; ++j) {
        if (ss[i][j] != '#') continue;
        for (int k = 0; k < 3; ++k) {
            if (ss[i + 1][j + dy[k]] == 'X') {
                r[j] = 'X';
            }
        }
    }
    return r;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    cin >> n;
    vector<string> ss;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        ss.push_back(s);
    }
    for (int i = n - 2; i >= 0; --i) {
        ss[i] = conv(ss, i);
    }

    for (auto& s : ss) {
        cout << s << endl;
    }
    
    return 0;
}
