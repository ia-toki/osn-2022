#include <bits/stdc++.h>

using namespace std;

long long n,a[100069],ps[100069];

int main()
{
	long long t,rr,i,k,p,z;
	
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
	for(rr=0;rr<t;rr++)
	{
		scanf("%lld",&k);
		z=0;
		for(i=1;i<=n;i++)
		{
			p=lower_bound(ps,ps+n+1,ps[i]-k)-ps;
			z+=ps[i]-ps[p]==k;
		}
		printf("%lld\n",z);
	}
}
