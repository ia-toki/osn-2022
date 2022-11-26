#include <bits/stdc++.h>

using namespace std;

const int MXQ = 1e5;
long long N, Q, X[MXQ + 69];

int main()
{
    long long i, rem, quot, ans;
    
    scanf("%lld%lld", &N, &Q);
    for(i = 0; i < Q; i++)
    {
        scanf("%lld", &X[i]);
        ans = 0;
        rem = X[i] % (N + 1);
        quot = X[i] / (N + 1);
        if(rem == 0)
        {
            ans += max(N / 2 - quot + 1, 0ll);
        }
        if(1 <= rem && rem <= (N + 1) / 2 && quot <= rem - 1)
        {
            ans++;
        }
        if((N + 1) / 2 + 1 <= rem && quot <= rem - (N + 1) / 2 - 1)
        {
            ans++;
        }
        rem = X[i] % (N + 2);
        quot = X[i] / (N + 2);
        if(rem == 0)
        {
            ans += max((N + 1) / 2 - 1 - quot + 1, 0ll);
        }
        printf("%lld\n", ans);
    }
}