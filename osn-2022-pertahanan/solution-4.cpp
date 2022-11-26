#include <bits/stdc++.h>

using namespace std;

long long n,a[100069],ps[100069];

int main()
{
	long long t,rr,i,j,k,z;
	
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
		for(j=0,i=1;i<=n;i++)
		{
			for(;ps[j]<ps[i]-k;j++);
			z+=ps[i]-ps[j]==k;
		}
		printf("%lld\n",z);
	}
}
