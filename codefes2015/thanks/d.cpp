#include <bits/stdc++.h>
using namespace std;
int main()
{
	int N, M, s, sum = 0, a, b, c;
	int stu[50][50];
	vector<int> know;
	vector<int> stus;
	cin >> N;
	for (int i = 0; i < N;++i) {
		cin >> s;
		for (int j = 0; j < N; ++j) stu[i][j] = -1;
		stu[i][i] = s;
		know.push_back(1);
		stus.push_back(s);
		sum += s;
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> c;
		if (a == 0) {
			stu[b-1][c-1] = stu[c-1][c-1];
			if (know[b-1] < N) know[b-1]++;
			stus[b-1] += stu[c-1][c-1];
			if (know[b-1] == N-1) {
				for (int j = 0; j < N; ++j) {
					if (stu[b-1][j] == -1){
						stu[b-1][j] = sum-stus[b-1];
						break;
					}
				}
				stus[b-1] = sum;
				know[b-1] = N;
			}
		}
		else {
			if (stu[b-1][c-1] != -1) cout << stu[b-1][c-1] << " " << stu[b-1][c-1] << endl;
			else if (sum - stus[b-1] <= 100) cout << 0 << " " << sum-stus[b-1] << endl;
			else if (sum - stus[b-1] <= (N - know[b-1] - 1) * 100) cout << "0 100" << endl;
			else cout << (sum-stus[b-1])%100 << " " << 100 << endl;
		}
	}
	return 0;
}
