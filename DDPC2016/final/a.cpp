#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    int x[] = {100000,50000,30000,20000,10000};
    int id[100];
    cin >> N;
    for (int i = 0, t; i < N; ++i) {
        cin >> t;
        if (i < 5) id[t-1] = x[i];
        else id[t-1] = 0;
    }

    for (int i = 0; i < N; ++i) {
        cout << id[i] << endl;
    }

    return 0;
}
