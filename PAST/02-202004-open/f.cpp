#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <functional>
#include <queue>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);


    int n;
    cin >> n;

    vector<priority_queue<int>> bs(n);
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        bs[a-1].push(b);
    }

    priority_queue<int> merged;
    vector<int> x;
    for (int i = 0; i < n; ++i) {
        while (!bs[i].empty()) {
            merged.push(bs[i].top());
            bs[i].pop();
        }
        x.push_back(merged.top());
        merged.pop();
    }
    
    for (int k = 0, p = 0; k < n; ++k) {
        p += x[k];
        cout << p << endl;
    }

    return 0;
}
