#include <bits/stdc++.h>
#include <cassert>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const int INF = 1e8;

using namespace std;

const int N = 100;
using Row = array<int, N+2>;
using Field = array<Row, N+2>;

ll calcBasicScore(Field a) {
    ll score = 200000000;
    for (int y = 1; y <= N; ++y) {
        for (int x = 1; x <= N; ++x) {
            score -= abs(a[y][x]);
        }
    }
    return score;
}

Field subtractPyramid(Field a, int x, int y, int h) {
    Field subtracted(a);
    for (int j = max(y - h + 1, 1); j <= min(y + h - 1, N); ++j) {
        for (int i = max(x - h + 1, 1); i <= min(x + h - 1, N); ++i) {
            subtracted[j][i] -= max(0, h - abs(x - i) - abs(y - j));
        }
    }
    return subtracted;
}

tuple<int, int, int> getTop(Field a) {
    array<pair<int, int>, N + 2> xmax;
    xmax.fill(make_pair(0, -INF));
    for (int y = 1; y <= N; ++y) {
        Row xs = a[y];
        Row::iterator xmaxItr = max_element(xs.begin(), xs.end());
        int x = distance(xs.begin(), xmaxItr);
        int h = *xmaxItr;
        xmax[y] = make_pair(x, h);
        //cerr << x << "," << y << "," << h << endl;
    }

    auto maxItr = max_element(xmax.begin(), xmax.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    int y = distance(xmax.begin(), maxItr);
    int x = maxItr->first;
    int h = maxItr->second;

    //cerr << x << "," << y << "," << h << endl;

    return make_tuple(x, y, h);
}

int main() {
    ios::sync_with_stdio(false);

    Field A;
    A[0].fill(-INF);
    A[N + 1].fill(-INF);
    for (int y = 1; y <= N; ++y) {
        A[y][0] = A[y][N + 1] = -INF;
        for (int x = 1; x <= N; ++x) {
            cin >> A[y][x];
        }
    }

    vector<int> X, Y, H;

    for (int i = 0; i < 1000; ++i) {
        tuple<int, int, int> top = getTop(A);
        int x = get<0>(top), y = get<1>(top), z = get<2>(top);
        if (z <= 0) break;
        //cerr << x << "," << y << ";" << z << endl;
        int minNeighbor = min({A[y - 1][x], A[y + 1][x], A[y][x - 1], A[y][x + 1]});
        if (minNeighbor != -INF && minNeighbor <= 0) break;
        int maxNeighbor = max({A[y - 1][x], A[y + 1][x], A[y][x - 1], A[y][x + 1]});
        
        cerr << "\t" << A[y - 1][x] << endl;
        cerr << A[y][x - 1] << "\t" << A[y][x] << "\t" << A[y][x + 1] << endl;
        cerr << "\t" << A[y + 1][x] << endl;

        //cerr << x << "," << y << ";" << z << "," << A[x][y-1] << "," << A[x][y+1] << "," << A[x-1][y] << "," << A[x+1][y] << endl;
        int h = min(max(minNeighbor, 1), 100);
        if (h <= 0) break;
        //cerr << x << "," << y << "," << z << ";" << maxNeighbor << endl;

        cerr << x << "," << y << "," << z << ";" << h << endl;

        A = subtractPyramid(A, x, y, h);

        cerr << "\t" << A[y - 1][x] << endl;
        cerr << A[y][x - 1] << "\t" << A[y][x] << "\t" << A[y][x + 1] << endl;
        cerr << "\t" << A[y + 1][x] << endl;

        X.push_back(x);
        Y.push_back(y);
        H.push_back(h);
        /*
        for (auto r : A) {
            for (auto c : r) {
                cerr << c << " ";
            }
            cerr << endl;
        }
*/
        //cerr << x << "," << y << "," << h << " -> " << calcBasicScore(A) << endl;
    }

    for (auto r : A) {
        for (auto c : r) {
            cerr << c << " ";
        }
        cerr << endl;
    }

    /*
    for (int y = 1; y <= N; ++y) {
        for (int x = 1; x <= N; ++x) {
            cerr << A[x][y] << " ";
        }
        cerr << endl;
    }
    */

    cout << X.size() << endl;
    for (int i = 0; i < X.size(); ++i) {
        cout << X[i] - 1 << " " << Y[i] - 1 << " " << H[i] << endl;
    }

    return 0;
}
