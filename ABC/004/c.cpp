#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

const int INF = 1e8;

int main() {
    vector<int> a(6);
    iota(begin(a), end(a), 1);

    int N;
    cin >> N;

    N %= 30;

    for (int i = 0; i < N; ++i) {
        swap(a[i % 5], a[i % 5 + 1]);
    }

    for (auto&& x : a) {
        cout << x;
    }
    cout << endl;

    return 0;
}
