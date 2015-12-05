/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair < ll, ll > llll;
typedef vector < int > vi;
#define mp make_pair
#define pb push_back
#define F first
#define S second

/******************************************************************************************************************************************
      
Question: Find ncr%p where n can be very big, p is square free number with prime factors less than LIM

******************************************************************************************************************************************/
#define LIM 100
ll factorial[LIM+1];
// For numbers with squarefree divisors ... 
vi factors(ll a)
{
	vi facs;
	int i=2;
	while(a!=1)
	{
		if(a%i==0)
		{
			a/=i;
			facs.pb(i);
		}
		i++;
	}
	return facs;
}
llll euclid_gcd(ll a, ll b)
{
	if(!b)
		return mp(1ll,0ll);
	llll prev=euclid_gcd(b,a%b);
	ll x=prev.F;
	ll y=prev.S;
	return mp(y,x-(a/b)*y);
}
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
// Works only when m is prime
ll inverse_modulo(ll a, ll m)
{
	return exponent(a,m-2,m);
}
ll lucas(ll n, ll r,ll m)
{
	ll x,y;
	if(n<r)
		return 0;
	ll res=1;
	while(n)
	{
		x=n%m;
		y=r%m;
		if(x<y)
			return 0;
		res=(res*(factorial[x]%m))%m;
		res=(res*inverse_modulo(factorial[y],m))%m;
		res=(res*inverse_modulo(factorial[x-y],m))%m;
		n/=m;
		r/=m;
	}
	return res;
}
ll NCR(ll n,ll r, ll m)
{
	if(n<r || m==1)
		return 0;
	vi facs=factors(m);
	factorial[0]=1;
	for(int i=1;i<=LIM;i++)
		factorial[i]=(i*factorial[i-1])%m;
	ll a=facs[0];
	ll result=lucas(n,r,a);
	for(int i=1;i<facs.size();i++)
	{
		// CRT
		llll euc=euclid_gcd(a,facs[i]);
		ll temp=lucas(n,r,facs[i]);
		result=(euc.F*a*temp+euc.S*facs[i]*result)%m;
		result=(result+m)%m;
		a*=facs[i];
	}
	return result;

}
int main()
{
	ll n,r,m;
	cin >> n >> r >> m;
	cout << NCR(n,r,m) << "\n";
	return 0;
}
