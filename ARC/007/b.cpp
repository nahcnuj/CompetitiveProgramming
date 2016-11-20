#include <iostream>
using namespace std;

int main()
{
	int N, M, disk[100+1], d, a;
	cin >> N >> M;
	for (int i = 0; i < N+1; ++i) disk[i] = i;
	for (int i = 0; i < M; ++i)
	{
		cin >> d;
		for (int j = 0; j < N+1; ++j)
		{
			if (disk[j] == d)
			{
				swap(disk[0], disk[j]);
				break;
			}
		}
	}
	for (int i = 1; i < N+1; ++i) cout << disk[i] << endl;
	return 0;
}