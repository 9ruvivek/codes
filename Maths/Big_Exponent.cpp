/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
Question: Find a^b%m where a and b are very big and a coprime to m

******************************************************************************************************************************************/
#define PHI 10000001
ll phi[PHI];
inline void init_phisum()
{
	for(ll i=1;i<PHI;i++)
		phi[i]=(i&1)?i:i/2;
	for(ll i=3;i<PHI;i+=2)
		if(phi[i]==i)
			for(ll j=i;j<PHI;j+=i)
				phi[j]-=phi[j]/i;
	for(int i=1;i<PHI;i++)
		phi[i]+=phi[i-1];
}
inline ll phisum(ll n)
{
	if(n<PHI)
		return phi[n];
	ll ret=(n*(n+1))/2;
	ll sq=2;

	while(sq*sq<=n)
	{
		ret-=phisum(n/sq);
		sq++;
	}
	sq=n/sq;
	ll cnt;
	while(sq)
	{
		cnt=n/sq-n/(sq+1); // Number of i's such that [n/i] is equal to sq
		ret-=cnt*phi[sq];
		sq--;
	}
	return ret;
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
int main()
{
	init_phisum();
	int testcases;
	cin >> testcases;
	string a,b;
	ll x,y,m;
	while(testcases--)
	{
		cin >> a >> b >> m;
		x=y=0;
		for(int i=0;i<a.length();i++)
			x=(x*10ll+(ll)(a[i]-'0'))%m;
		ll phim=phisum(m)-phisum(m-1);
		// a^(phi[n])=1(mod n) if a coprime to n
		for(int i=0;i<b.length();i++)
			y=(y*10ll+(ll)(b[i]-'0'))%phim;
		cout << exponent(x,y,m) << "\n";
	}
	return 0;
}
