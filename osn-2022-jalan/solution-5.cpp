#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];
bitset<MXN + 69> T;

int main()
{
	long long i, j, r, sign, k, sm, sm2, ans = 0;
	bool bad;
	
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
		for(j = i; j <= N; j++)
		{
			sm = 0;
			sm2 = 0;
			bad = 0;
			for(r = j; r >= i; r--)
			{
				sm += A[r];
				if(sm < 0)
				{
					bad = 1;
					break;
				}
				sm2 = (sm2 + sm) % MOD;
			}
			if(!bad)
			{
				ans = (ans + sm2) % MOD;
			}
		}
	}
	printf("%lld\n", ans);
}
