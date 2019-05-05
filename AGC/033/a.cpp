#include <bits/stdc++.h>

using namespace std;

int main() {
	int H, W;
	cin >> H >> W;

	vector<string> A(H);
	vector<vector<int>> d(H, vector<int>(W, 1e9));
	queue<pair<int,int>> q;
	for (int i = 0; i < H; ++i) {
		cin >> A[i];
		for (int j = 0; j < W; ++j) {
			if (A[i][j] == '#') {
				d[i][j] = 0;
				q.emplace(j, i);
			}
		}
	}

	int dx[]{1, -1, 0, 0}, dy[]{0, 0, 1, -1};
	int ans = 0;
	while (!q.empty()) {
		auto p = q.front(); q.pop();
		int x = p.first, y = p.second;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || W <= nx || ny < 0 || H <= ny || A[ny][nx] == '#') {
				continue;
			}
			A[ny][nx] = '#';
			q.emplace(nx, ny);
			ans = max(d[ny][nx] = d[y][x] + 1, ans);
		}
	}

	cout << ans << endl;

	return 0;
}