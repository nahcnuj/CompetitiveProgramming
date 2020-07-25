#include <bits/stdc++.h>

using namespace std;

bool next(vector<int>& orig) {
    for (int i = 0; i < orig.size(); ++i) {
        if (++orig[i] <= 3) {
            return true;
        }
        orig[i] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);

    int r, g, b, K;
    cin >> r >> g >> b >> K;

    vector<int> choice(K);
    while (next(choice)) {
        vector<int> cards {r, g, b};
        for (int c : choice) {
            cards[c - 1] *= 2;
            //cerr << cards[0] << "," << cards[1] << "," << cards[2] << endl;

            if (cards[1] > cards[0] && cards[2] > cards[1]) {
                cout << "Yes" << endl;
                return 0;
            }
        }
        //cerr << "--------" << endl;
    }

    cout << "No" << endl;

    return 0;
}
