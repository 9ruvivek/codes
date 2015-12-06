/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
/******************************************************************************************************************************************
      
      Question: Check if the given number is fibonacci or not
      Reference: Binet's Formula

******************************************************************************************************************************************/
bool is_square(ll n)
{
	ll t=sqrt(n);
	return t*t==n;
}
bool is_fibo(ll n)
{
	// True iff 5*n^2+4 or 5*n^2-4 is a perfect square
	return (n>=0) && (is_square(5*n*n+4) || is_square(5*n*n-4));
}
int main()
{
	ll n;
	cin >> n;
	if(is_fibo(n))
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}

