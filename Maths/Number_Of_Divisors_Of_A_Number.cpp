/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;


/******************************************************************************************************************************************
      
      Question: Find Number of divisors of a number N

      Reference: http://codeforces.com/blog/entry/22317

      Complexity: N^(1/3) + seive complexity

******************************************************************************************************************************************/
vector<ll> prim;
#define SEIVE 1000001
bitset<SEIVE> ok;
inline void seive(){
	ok.set();
	for(int i=2;i*i<SEIVE;i++)
		if(ok[i])
			for(int j=i<<1;j<SEIVE;j+=i)
				ok.reset(j);
	for(int i=2;i<SEIVE;i++)
		if(ok[i])
			prim.push_back((ll)i);
}
unsigned long long modmult(unsigned long long a, unsigned long long b, unsigned long long mod)
{
	unsigned long long sum;
	if ((a == 0) || (b < (mod / a)))
		return (a * b) % mod;
	sum = 0;
	while (b > 0)
	{
		if (b & 1)
			sum = (sum + a) % mod;
		b >>= 1;
		a = (a << 1) % mod;
	}
	return sum;
}
unsigned long long modpow(unsigned long long a, unsigned long long b, unsigned long long mod)
{
	unsigned long long product, psequence;
	product = 1;
	psequence = a;
	while (b > 0)
	{
		if (b & 1)
			product = modmult(product, psequence, mod);
		b >>= 1;
		psequence = modmult(psequence, psequence, mod);
	}
	return product;
}
bool miller_rabin(unsigned long long n)
{
	int count, i, j;
	unsigned long long a, d, x;
	if (n == 2)
		return 1;
	if ((n < 2) || (!(n & 1)))
		return 0;
	d = n - 1;
	count = 0;
	while (!(d & 1))
	{
		d >>= 1;
		count++;
	}
	for (i = 0; i < 60; i++)
	{
		a = (rand() % (n - 1)) + 1;
		x = modpow(a, d, n);
		if ((x == 1) || (x == n - 1))
			continue;
		for (j = 1; j < count; j++)
		{
			x = modpow(x, 2, n);
			if (x == 1)
				return 0;
			if (x == n - 1)
				break;
		}
		if (x == n - 1)
			continue;
		return 0;
	}
	return 1;
}
ll res,cnt,n;
int main()
{
	cin >> n;
	res=cnt=1;
	seive();
	for(int i=0;i<prim.size();i++)
	{
		if(prim[i]*prim[i]*prim[i]>n)
			break;
		cnt=1;
		while(n%prim[i]==0)
		{
			n/=prim[i];
			cnt++;
		}
		res*=cnt;
	}
	if(n==1)
	{
		cout << res << "\n";
		return 0;
	}
	if(miller_rabin((unsigned long long)n))
		res*=2;
	else
	{
		ll sq=sqrt(n);
		if(sq*sq==n && miller_rabin((unsigned long long)sq))
			res*=3;
		else
			res*=4;
	}
	cout << res << "\n";
	return 0;
}
