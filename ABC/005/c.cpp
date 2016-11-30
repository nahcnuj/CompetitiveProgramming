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
    int T, N, M;
    cin >> T >> N;
    vector<int> A, B;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        A.push_back(x);
    }
    cin >> M;
    for (int i = 0, x; i < M; ++i) {
        cin >> x;
        B.push_back(x);
    }

    if (N < M) {
        cout << "no" << endl;
        return 0;
    }
    
    for (int bi = 0, ai = 0; bi < M; ++bi, ++ai) {
        while (A[ai] + T < B[bi]) {
            ++ai;
            if (ai >= N) {
                cout << "no" << endl;
                return 0;
            }
        }
        if (A[ai] > B[bi]) {
            cout << "no" << endl;
            return 0;
        }
    }

    cout << "yes" << endl;

    return 0;
}
