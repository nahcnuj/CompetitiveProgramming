#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
using Pii = pair<int, int>;
    
const ll INF = (ll)1e11;
    
int main() {
    string s;
    cin >> s;
    
    string w = "";
    for (auto itr = s.rbegin(); itr != s.rend(); ++itr) {
        if (w == "dreamer" || w == "eraser") {
            w = *itr;
        }
        else if (w == "dream" || w == "erase") {
            w = *itr;
        }
        else if (w.length() < 7) {
            w = *itr + w;
        } 
        else {
            cout << "NO" << endl;
            return 0;
        }
    }
    if (w == "dreamer" || w == "eraser" || w == "dream" || w == "erase") {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    
    return 0;
}