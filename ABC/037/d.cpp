#include <iostream>
#include <set>
#include <queue>
#include <utility>
using namespace std;
const int MOD = 1000000007;
int a[1000][1000], dp[1000][1000];
int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
int h, w;

long long int dfs(int x, int y) {
	if (dp[x][y] != -1) return dp[x][y];
	
	long long int ans = 1;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || w <= nx || ny < 0 || h <= ny
		    || a[x][y] >= a[nx][ny]) {
			continue;
		}
		ans += dfs(nx, ny);
	}
	dp[x][y] = ans % MOD;
	return ans;
}

int main() {
	cin >> h >> w;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int z;
			scanf("%d", &z);
			a[x][y] = z;
			
			dp[x][y] = -1;
		}
	}
	
	long long int ans = 0;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			ans += dfs(x, y);
			ans %= MOD;
		}
	}
	cout << ans << endl;
	return 0;
}
