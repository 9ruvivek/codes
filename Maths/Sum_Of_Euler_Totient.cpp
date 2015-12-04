/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: Find Sum of Euler Totient from 1 to N

      Reference: https://codechef_shared.s3.amazonaws.com/upfiles/phisum.jpg

      Complexity: Can be Considered to be atmost O(sqrt(N)) + Time to precompute phisum till a fixed limit(using normal way)

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
int main()
{
	init_phisum();
	int testcases;
	cin >> testcases;
	ll n;
	while(testcases--)
	{
		cin >> n;
		cout << phisum(n) << "\n";
	}
	return 0;
}
