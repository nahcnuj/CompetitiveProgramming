#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

char c[1000][1000];
int t[1000][1000];
bool b[1000][1000];
const long long INF = 1e18;
const int dx[] = {-1,-1,-1,0,1,1,1,0}, dy[] = {-1,0,1,1,1,0,-1,-1};
queue< pair<int,int> > q[2];
int main()
{
	int H,W;
	cin >> H >> W;
	for (int y = 0; y < H; ++y) {
		for (int x = 0; x < W; ++x) {
			cin >> c[x][y];
			if (x > 0) {
				if (c[x-1][y] == '.') ++t[x][y];
				if (c[x][y] == '.') { ++t[x-1][y];  }
			}
			if (y > 0) {
				if (x+1 < W && c[x+1][y-1] == '.') ++t[x][y];
				if (c[x][y-1] == '.') ++t[x][y];
				if (c[x][y] == '.') ++t[x][y-1];
				if (x+1 < W && c[x][y] == '.') ++t[x+1][y-1];
			}
			if (x > 0 && y > 0) {
				if (c[x-1][y-1] == '.') ++t[x][y];
				if (c[x][y] == '.') ++t[x-1][y-1];
			}
			if (x > 0 && y > 0 && c[x-1][y-1] != '.' && t[x-1][y-1] >= c[x-1][y-1]-'0') {
				q[0].push( make_pair(x-1, y-1) );
				b[x-1][y-1] = true;
			}
		}
	}
	long long int z = 0, u = 0, v = 1;
	while (!q[u].empty()) {
		while (!q[u].empty()) {
			int xx = q[u].front().first, yy = q[u].front().second;
			q[u].pop();
			b[xx][yy] = true;
			c[xx][yy] = '.';
			for (int i = 0; i < 8; ++i) {
				if (0 < xx+dx[i] && xx+dx[i] < W && 0 < yy+dy[i] && yy+dy[i] < H) {
					++t[xx+dx[i]][yy+dy[i]];
					if (!b[xx+dx[i]][yy+dy[i]] && c[xx+dx[i]][yy+dy[i]] != '.' && t[xx+dx[i]][yy+dy[i]] >= c[xx+dx[i]][yy+dy[i]]-'0') {
						q[v].push( make_pair(xx+dx[i], yy+dy[i]) );
						b[xx+dx[i]][yy+dy[i]] = true;
					}
				}
			}
		}
		++z;
		swap(u,v);
	}
	cout << z << endl;
	return 0;
}
