#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);


    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        a.push_back(x);
    }

    vector<int> r;
    for (int i = 1; i <= n; ++i) {
        int x = i;
        int j;
        for (j = 1; ; ++j) {
            x = a[x - 1];
            if (x == i) break;
        }
        r.push_back(j);
    }

    for (int i = 0; i < n; ++i) {
        cout << (i > 0 ? " " : "") << r[i];
    }
    cout << endl;

    return 0;
}
