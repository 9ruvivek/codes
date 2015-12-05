/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair < ll, ll > llll;
#define mp make_pair
#define F first
#define S second

/******************************************************************************************************************************************
      
      Question: Find two numbers x and y such that ax+by=gcd(a,b)

******************************************************************************************************************************************/
/*
 *  b*x + (a%b)*y = g
 *  b*x + (a-[a/b]*b)*y = g
 *  b*x + a*y - (b*y)*[a/b] = g
 *  a*y + b*(x-[a/b]*y) = g
*/
llll euclid_gcd(ll a, ll b)
{
	if(!b)
		return mp(1ll,0ll);
	llll prev=euclid_gcd(b,a%b);
	ll x=prev.F;
	ll y=prev.S;
	return mp(y,x-(a/b)*y);
}
int main()
{
	ll a,b;
	cin >> a >> b;
	llll ret=euclid_gcd(a,b);
	cout << ret.F << "*"  << a << " + " << ret.S << "*" << b << " = " << ret.F*a+ret.S*b << "\n";
	return 0;
}
