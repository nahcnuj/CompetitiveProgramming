#include <cstdio>

int a[1000000] = {0, 0, 1};

int main() {
    int n;
    
    std::scanf("%d", &n);
	
	if (n > 3) {
        for (int i = 3; i < n; ++i) a[i] = (a[i-3] + a[i-2] + a[i-1])%10007;
    }
    std::printf("%d\n", a[n-1]);
    
    return 0;
}
