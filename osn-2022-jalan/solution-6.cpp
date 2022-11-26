#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];
bitset<MXN + 69> T;

int main()
{
	long long i, j, sign, k, sm, sm2, ans = 0;
	
	scanf("%lld", &N);
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
	}
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &k);
		T[i] = k - 1;
		sign = T[i] == 0 ? 1 : -1;
		A[i] *= sign;
	}
	for(i = 1; i <= N; i++)
	{
		sm = 0;
		sm2 = 0;
		for(j = i; j >= 1; j--)
		{
			sm += A[j];
			if(sm < 0)
			{
				break;
			}
			sm2 = (sm2 + sm) % MOD;
			ans = (ans + sm2) % MOD;
		}
	}
	printf("%lld\n", ans);
}
