#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const ll NN = 2e5 + 5;
const ll mo = 1e9 + 7;
ll n, q, a[NN];
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n, q;
    cin >> n >> q;
    for(ll i = 1; i <= n; i++)
        if(i % 2 == 1)
            a[i] = (i + 1) / 2;
        else
            a[i] = n + 1 - i / 2;
    while(q--)
    {
        ll X, jaw = 0;
        cin >> X;
        for(ll i = 1; i <= n; i++)
        {
            ll sum = 0;
            for(ll j = i; j <= n; j++)
            {
                sum += a[j];
                jaw += (sum == X);
            }
        }
        cout << jaw << "\n";
    }
}