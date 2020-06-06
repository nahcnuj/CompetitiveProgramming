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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int A,R,N;
    cin >> A>>R>>N;

    long long int an = A;
    for (int i = 2; i <= N; ++i) {
        an *= (long long int) R;
        if (an > 1000000000ll) {
            cout << "large" << endl;
            return 0;
        }
    }
    cout << an << endl;

    return 0;
}
