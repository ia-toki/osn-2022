#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];

int main()
{
	long long i, j, r, ans = 0;
	
	scanf("%lld", &N);
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
		for(j = 1; j <= i; j++)
		{
			for(r = j; r <= i; r++)
			{
				ans = (ans + A[r] * (r - (j - 1))) % MOD;
			}
		}
	}
	printf("%lld\n", ans);
}
