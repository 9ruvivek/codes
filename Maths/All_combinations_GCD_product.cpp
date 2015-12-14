/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: Find GCD of all pairs in given input


******************************************************************************************************************************************/
#define N 100001
#define MOD 1000000007
int n;
ll arr[N],cnt[N],divcnt[N],gcdcnt[N];
ll exponent(ll a, ll b, ll m)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=(res*a)%m;
		a=(a*a)%m;
		b>>=1;
	}
	return res;
}
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	for(int i=1;i<N;i++)
		for(int j=i;j<N;j+=i)
			divcnt[i]+=cnt[j];
	for(int i=N-1;i>0;i--)
	{
		gcdcnt[i]=(exponent(2,divcnt[i],MOD-1)+(MOD-1)-1)%(MOD-1);
		for(int j=2*i;j<N;j+=i)
		{
			gcdcnt[i]-=gcdcnt[j];
			gcdcnt[i]%=MOD-1;
			gcdcnt[i]+=MOD-1;
			gcdcnt[i]%=MOD-1;
		}
	}
	ll res=1;
	for(ll i=1;i<N;i++)
		res=(res*exponent(i,gcdcnt[i],MOD))%MOD;
	cout << res << "\n";
	return 0;
}

