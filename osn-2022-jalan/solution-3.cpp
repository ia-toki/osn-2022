#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];

int main()
{
	long long i, j, ans = 0;
	
	scanf("%lld", &N);
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
	}
	for(i = 1; i <= N; i++)
	{
		for(j = i; j <= N; j++)
		{
			ans = (ans + A[j] * (j - (i - 1)) % MOD * (N + 1 - j)) % MOD;
		}
	}
	printf("%lld\n", ans);
}
