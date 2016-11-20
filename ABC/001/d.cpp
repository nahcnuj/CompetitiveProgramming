#include <bits/stdc++.h>
using namespace std;
int main() {
	int N;
	scanf("%d",&N);
	vector<pair<int,int>> log;
	for (int i = 0; i < N; ++i) {
		int S, E;
		scanf("%d-%d",&S,&E);
		log.push_back(make_pair(S-S%5,E-E%5+(E%5>0)*5+(E%100>55)*40));
	}
	sort(log.begin(),log.end());
	int ps=log[0].first, pe=log[0].second;
	for (int i = 0; i < N; ++i) {
		int s = log[i].first, e = log[i].second;
		if (pe < s) {
			printf("%04d-%04d\n",ps,pe);
			ps = s, pe = e;
		}
		else if (ps <= s && s <= pe && pe <= e) pe = e;
	}
	printf("%04d-%04d\n",ps,pe);
	return 0;
}
