#include <bits/stdc++.h>

using ll = long long;
using Pii = std::pair<int, int>;
using Pll = std::pair<ll, ll>;

const ll INF = (ll)1e16;

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int lookat = 1, c = 0;
    vector<int> nums;   // 1-0-1-0-1
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0' + lookat) {
            ++c;
        } else {
            nums.push_back(c);
            lookat = 1 - lookat;
            c = 1;
        }
    }
    if (c > 0) nums.push_back(c);
    
    if (nums.size() % 2 == 0) nums.push_back(0);

    int ans = 0;
    int left = 0, right = 0, tmp = 0; // [left, right) の sum
    for (int i = 0; i < nums.size(); i += 2) {
        int nextLeft = i, nextRight = min(i + 2 * k + 1, (int)nums.size());

        while (left < nextLeft) {
            tmp -= nums[left];
            ++left;
        }

        while (right < nextRight) {
            tmp += nums[right];
            ++right;
        }
        ans = max(tmp, ans);
    }

    cout << ans << endl;

    return 0;
}
