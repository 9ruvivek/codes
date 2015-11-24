/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: Find Number of Coprimes of N for many values of N

      Reference: https://en.wikipedia.org/wiki/Euler's_totient_function

      Complexity: Can be Considered to be atmost O(10*n)

******************************************************************************************************************************************/

#define PHI 10000010
int phi[PHI];
inline void Totient()
{
	for(int i=1;i<=PHI;i++)
		phi[i]=(i&1)?i:i/2;

	for(int i=3;i<PHI;i+=2)
		if(phi[i]=i)
			for(int j=i;j<PHI;j+=i)
				phi[j]-=phi[j]/i;
}
int n;
int TestCases;
int main()
{
	Totient();
	cin >> TestCases;
	while(TestCases--)
	{
		cin >> n;
		cout << n << " has " << phi[n] << " coprimes less than it\n";
	}
	return 0;
}

