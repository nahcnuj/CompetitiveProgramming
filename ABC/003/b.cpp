#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

const string a = "atcoder";

int main() {
    string S, T;
    cin >> S >> T;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == '@' && T[i] != '@') {
            for (int j = 0; j < a.length(); j++) {
                if (T[i] == a[j]) {
                    S[i] = T[i];
                    break;
                }
            }
            if (S[i] == '@') {
                cout << "You will lose" << endl;
                return 0;
            }
        }
        else if (S[i] != '@' && T[i] == '@') {
            for (int j = 0; j < a.length(); j++) {
                if (S[i] == a[j]) {
                    T[i] = S[i];
                    break;
                }
            }
            if (T[i] == '@') {
                cout << "You will lose" << endl;
                return 0;
            }
        }
        else if (S[i] != T[i]) {
            cout << "You will lose" << endl;
            return 0;
        }
    }
    cout << "You can win" << endl;
    return 0;
}
