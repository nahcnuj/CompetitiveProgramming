#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<int, int> P;
const int INF = 1e8;
const int dx[] = {1, 0, -1, 0, 1, -1}, dy[] = {0, 1, 0, -1, 1, -1};

int main()
{
	int W, H, N, x, y, res = 0;
	P p[1000];
	
	cin >> W >> H >> N;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		p[i] = make_pair(x, y);
	}
	
	//p[i]Ç©ÇÁp[i+1]Ç÷ÇÃç≈è¨ÇÃìπ
	for (int i = 0; i < N-1; ++i) {
		int ddx = p[i].first - p[i+1].first;
		int ddy = p[i].second - p[i+1].second;
		
		if (ddx*ddy >= 0) res += max(abs(ddx), abs(ddy));
		else res += abs(ddx) + abs(ddy);
		/*
		map<P, int> dist;
		queue<P> que;
		
		que.push( make_pair(p[i].first, p[i].second) );
		dist[make_pair(p[i].first, p[i].second)] = 0;
		
		while (que.size() != 0) {
			P now = que.front(); que.pop();
			if (now == p[i+1]) break;
			
			//ç∂,è„,âE,â∫,âEè„,ç∂â∫
			for (int j = 0; j < 6; ++j) {
				P next = make_pair(now.first+dx[j], now.second+dy[j]);
				
				if (1 <= next.first && next.first <= W &&
					1 <= next.second && next.second <= H &&
					dist.count(next) == 0) {
						que.push(next);
						dist[next] = dist[now]+1;
				}
			}
		}
		res += dist[ p[i+1] ];
		*/
	}
	cout << res << endl;
	
	return 0;
}
