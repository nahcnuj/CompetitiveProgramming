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

string table[5][10] = {
    { "###", ".#.", "###","###", "#.#", "###","###","###","###","###" },
    { "#.#","##.","..#","..#","#.#","#..","#..","..#","#.#","#.#" },
    { "#.#",".#.","###","###","###","###","###","..#","###","###" },
    { "#.#",".#.","#..","..#","..#","..#","#.#","..#","#.#","..#" },
    { "###","###","###","###","..#","###","###","..#","###","###" }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N;
    cin >> N;

    string s[5];
    for (int i = 0; i < 5; ++i) {
        cin >> s[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k <= 9; ++k) {
            for (int j = 0; j < 5; ++j) {
                auto&& t = s[j].substr(i * 4 + 1, 3);
                if (t != table[j][k]) {
                    goto nextnumber;
                }
            }
            cout << k;
            break;

            nextnumber:;
        }
    }
    cout << endl;

    return 0;
}
