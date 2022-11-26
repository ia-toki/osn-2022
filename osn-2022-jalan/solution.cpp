#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, stkN = 0, A[MXN + 69], pref[MXN + 69], stk[MXN + 69], pref2[MXN + 69], pref3[MXN + 69];
bitset<MXN + 69> T;

inline long long tri(long long x)
{
	return x * (x + 1) / 2 % MOD;
}

inline long long query(long long lh, long long rh)
{
	return (pref3[rh] + MOD - pref3[lh - 1] + MOD - (pref2[rh] + MOD - pref2[lh - 1]) * (lh - 1) % MOD) % MOD;
}

int main()
{
	long long i, sign, k, ans = 0;
	
	scanf("%lld", &N);
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &A[i]);
	}
	stk[0] = -1;
	stkN++;
	stk[stkN] = 0;
	for(i = 1; i <= N; i++)
	{
		scanf("%lld", &k);
		T[i] = k - 1;
		sign = T[i] == 0 ? 1 : -1;
		A[i] *= sign;
		pref[i] = pref[i-1] + A[i];
		pref2[i] = (pref2[i-1] + pref[i-1] % MOD + MOD) % MOD;
		pref3[i] = (pref3[i-1] + (pref[i-1] % MOD + MOD) * i) % MOD;
		while(stkN > 0 && pref[stk[stkN]] <= pref[i])
		{
			stkN--;
		}
		ans = (ans + (pref[i] % MOD + MOD) * tri(i - (stk[stkN] + 1)) + MOD - query(stk[stkN] + 2, i)) % MOD;
		stkN++;
		stk[stkN] = i;
	}
	printf("%lld\n", ans);
}
