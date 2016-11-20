#include <iostream>
#include <queue>
using namespace std;

int m[10+2][10+2];
const int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
int main()
{
	int s = 0;
	for (int y = 1; y <= 10; ++y) {
		for (int x = 1; x <= 10; ++x) {
			char c;
			cin >> c;
			m[x][y] = (c == 'o' ? 1 : -1);
			s += (c=='o' ? 1 : 0);
		}
	}
	for (int y = 1; y <= 10; ++y) {
		for (int x = 1; x <= 10; ++x) {
			queue<pair<int,int> > q;
			bool v[10+2][10+2] = {};
			q.push(make_pair(x,y));
			v[x][y] = true;
			int is = 0;
			while (!q.empty()) {
				int xx = q.front().first, yy = q.front().second;
				q.pop();
				++is;
				for (int i = 0; i < 4; ++i) {
					if (!v[xx+dx[i]][yy+dy[i]] && m[xx+dx[i]][yy+dy[i]] == 1) {
						v[xx+dx[i]][yy+dy[i]] = true;
						q.push(make_pair(xx+dx[i],yy+dy[i]));
					}
				}
			}
			if ((m[x][y] == 1 && is == s) || (m[x][y] == -1 && is == s+1)) {
				cout << "YES" << endl;
				return 0;
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
