#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pii = pair<int, int>;

const ll INF = 1000000000000ll;

string rev(string s) {
    for (int i = 0; i < s.length(); ++i) {
        s[i] = (s[i] == '0' ? '1' : '0');
    }
    return s;
}

int main() {ios::sync_with_stdio(false);
    ll cost[3];
    string t;
    cin >> cost[0] >> cost[1] >> cost[2] >> t;

    //if (t.length() > 10) return 0;

    ll ans = 0;

    set<string> al;
    vector<string> aa;
    queue<string> q;
    q.push(t);
    while (!q.empty()) {
        string x = q.front();
        al.insert(x);
        aa.push_back(x);
        q.pop();

        if (x.front() == '0') {
            q.push(x.substr(1));
        }
        if (x.back() == '1') {
            q.push(x.substr(0,x.length()-1));
        }
        auto rs = rev(x);
        if (al.count(rs) == 0) {
            q.push(rs);
        }
    }

    aa.erase(remove(aa.begin(), aa.end(), ""), aa.end());
    reverse(aa.begin(), aa.end());
    //for (auto&& x : aa) cout << x << endl;

    //return 0;

    map<string, ll> dp;
    dp[""] = 0;

    for (auto&& x : aa) {
        ll minc = INF;
        if (x.front() == '0') {
            //cerr << x.substr(1) << endl;
            minc = min(minc, dp[x.substr(1)] + cost[0]);
        }
        if (x.back() == '1') {
            minc = min(minc, dp[x.substr(0,x.length()-1)] + cost[1]);
        }
        if (dp.count(rev(x))) {
            minc = min(minc, dp[rev(x)] + cost[2]);
        }
        //cerr << x << ":" << minc << endl;
        //break;
        dp[x] = minc;
    }

    cout << dp[t] << endl;

    return 0;
}
