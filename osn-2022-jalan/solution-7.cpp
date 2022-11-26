#include <bits/stdc++.h>

using namespace std;

const long long MXN = 1e5, MOD = 1e9 + 7;
long long N, A[MXN + 69];
bitset<MXN + 69> T;

inline long long tri(long long x)
{
	return x * (x + 1) / 2 % MOD;
}

int main()
{
	long long i, j, sign, k, sm = 0, sm2 = 0, sm3 = 0, ans = 0;
	
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
	i = 0;
	while(i + 1 <= N && T[i + 1] == 1)
	{
		i++;
	}
	j = i + 1;
	while(i + 1 <= N)
	{
		i++;
		sm += A[i];
		sm2 = (sm2 + A[i] * (i - j + 1)) % MOD;
		sm3 = (sm3 + A[i] * tri(i - j + 1)) % MOD;
		while(j - 1 >= 1 && sm + A[j - 1] >= 0)
		{
			j--;
			sm += A[j];
			sm2 = (sm2 + sm) % MOD;
			sm3 = (sm3 + sm2) % MOD;
		}
		ans = (ans + sm3) % MOD;
	}
	printf("%lld\n", ans);
}
