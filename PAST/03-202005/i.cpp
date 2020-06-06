#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <functional>
#include <queue>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

using pint = pair<int,int>;

int dx[] = {1, 0, -1, 1, -1,  0};
int dy[] = {1, 1,  1, 0,  0, -1};

long long int N;
long long int calc(long long int i, long long int j) {
    return N * (i - 1ll) + j - 1ll;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    //int N;
    cin >> N;

    //vector<vector<long long int>> a(N+1, vector<long long int>(N+1));
    vector<long long int> R(N+1), C(N+1);     // a[R[i]][C[j]]
    for (int i = 1; i <= N; ++i) {
        R[i] = C[i] = i;
    /*    for (int j = 1; j <= N; ++j) {
            a[i][j] = N * (i - 1) + j - 1;
        }*/
    }

    int Q;
    cin >> Q;
    bool transpose = false;
    while (--Q >= 0) {
        //cerr << "R C" << endl;
        //for (int i = 1; i <= N; ++i) {
        //    cerr << R[i] << " " << C[i] << endl;
        //}

        int t; cin >>t;
        long long int A,B;
        if (t == 1) {
            cin >> A >> B;
            //cerr << "1R " << R[A] << R[B] << endl;
            //cerr << "1C " << C[A] << C[B] << endl;
            transpose ? swap(C[A], C[B]) : swap(R[A], R[B]);
            //cerr << "1R " << R[A] << R[B] << endl;
            //cerr << "1C " << C[A] << C[B] << endl;
        } else if (t == 2) {
            cin >> A >> B;
            //cerr << "2R " << R[A] << R[B] << endl;
            //cerr << "2C " << C[A] << C[B] << endl;
            transpose ? swap(R[A], R[B]) : swap(C[A], C[B]);
            //cerr << "2R " << R[A] << R[B] << endl;
            //cerr << "2C " << C[A] << C[B] << endl;
        } else if (t == 3) {
            transpose = !transpose;
        } else {
            cin >> A >> B;
            long long int i = R[transpose ? B : A], j = C[transpose ? A : B];
            cout << calc(i, j) << endl;
        }

/*
        cerr << endl;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                auto s = R[transpose ? j : i], t = C[transpose ? i : j];
                //cerr << s << t << " ";
                cerr << a[s][t] << " ";
            }
            cerr << endl;
        }
*/
    }

    return 0;
}
