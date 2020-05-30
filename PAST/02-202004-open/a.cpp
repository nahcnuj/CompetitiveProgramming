#include <iostream>
#include <string>
using namespace std;

int conv(string s) {
    int f;
    if (s[0] == 'B') {
        f = -((s[1] - '0') - 1);
    } else {
        f = (s[0] - '0');
    }
    return f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    string s, t;
    cin >> s >> t;
    int sf = conv(s), tf = conv(t);
    int d = tf - sf;
    if (d < 0) d *= -1;
    cout << d << endl;
    return 0;
}
