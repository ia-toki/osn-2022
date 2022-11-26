#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];

inline long long tri(long long x)
{
	return x * (x + 1) / 2 % MOD;
}

int main()
{
	long long i, ans = 0;
	
	scanf("%lld", &N);
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
		ans = (ans + A[i] * tri(i) % MOD * (N + 1 - i)) % MOD;
	}
	printf("%lld\n", ans);
}
