#include <bits/stdc++.h>

using namespace std;

long long n,a[100069],ps[100069];
map<long long,long long> fq;

int main()
{
	long long t,rr,i,j,k;
	
	scanf("%lld%lld",&n,&t);
	for(i=1;i<=n;i++)
	{
		if(i%2)
		{
			a[i]=(i+1)/2;
		}
		else
		{
			a[i]=n+1-i/2;
		}
		ps[i]=ps[i-1]+a[i];
	}
	for(i=1;i<=n;i++)
	{
		for(j=0;j<i;j++)
		{
			fq[ps[i]-ps[j]]++;
		}
	}
	for(rr=0;rr<t;rr++)
	{
		scanf("%lld",&k);
		printf("%lld\n",fq[k]);
	}
}
