#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long int dp[1000+1][1000+1] = {};
const long long INF = 1e18;
int main()
{
	int N,M,D[1000],C[1000];
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> D[i];
		for (int j = i+1; j <= M; ++j) dp[i][j] = INF;
	}
	for (int i = 0; i < M; ++i) cin >> C[i];
	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= min(i,N); ++j) {
			dp[i][j] = min( dp[i-1][j-1] + C[i-1]*D[j-1], dp[i-1][j] );
			//cerr << i << "," << j << ":" << dp[i][j] << endl;
		}
	}
	long long int r = INF;
	for (int i = N; i <= M; ++i) {
		if (dp[i][N] < r) r = dp[i][N];
		//cerr << dp[i][N] << endl;
	}
	cout << r << endl;
	return 0;
}
