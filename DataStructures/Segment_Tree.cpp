/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: Range Update and query

******************************************************************************************************************************************/
#define N 1000001
#define NLOGN 20000001
class segtree
{
	public:
		ll n;
		ll arr[N];
		ll st[NLOGN];
		ll lazy[NLOGN];
		void initialize();
		void construct(ll parent,ll left,ll right);
		void rangeadd(ll parent,ll start,ll end,ll left,ll right,ll value);
		ll rangesum(ll parent,ll start,ll end,ll left,ll right);

};
void segtree::initialize()
{
	for(int i=0;i<N;i++)
		arr[i]=0ll;
	for(int i=0;i<NLOGN;i++)
		st[i]=lazy[i]=0ll;
}
void segtree::rangeadd(ll parent,ll start,ll end,ll left,ll right,ll value)
{
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(start+end)>>1;
	ll len=end-start+1;
	if(lazy[parent])
	{
		st[parent]+=len*lazy[parent];
		if(len>1)
		{
			lazy[lchild]+=lazy[parent];
			lazy[rchild]+=lazy[parent];
		}
		lazy[parent]=0ll;
	}
	if(start>end || start>right || end<left)
		return;
	if(start>=left && end<=right)
	{
		st[parent]+=len*value;
		if(len>1)
		{
			lazy[lchild]+=value;
			lazy[rchild]+=value;
		}
		return;
	}
	rangeadd(lchild,start,mid,left,right,value);
	rangeadd(rchild,mid+1,end,left,right,value);
	st[parent]=st[lchild]+st[rchild];
	return;
}
ll segtree::rangesum(ll parent,ll start,ll end,ll left,ll right)
{
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(start+end)>>1;
	ll len=end-start+1;
	if(lazy[parent])
	{
		st[parent]+=len*lazy[parent];
		if(len>1)
		{
			lazy[lchild]+=lazy[parent];
			lazy[rchild]+=lazy[parent];
		}
		lazy[parent]=0ll;
	}
	if(start>end || start>right || end<left)
		return 0ll;
	if(start>=left && end<=right)
		return st[parent];
	ll lsum=rangesum(lchild,start,mid,left,right);
	ll rsum=rangesum(rchild,mid+1,end,left,right);
	return lsum+rsum;
}
void segtree::construct(ll parent,ll left,ll right)
{
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(left+right)>>1;
	if(left>right)
		return;
	if(left==right)
	{
		st[parent]=arr[left];
		return;
	}
	construct(lchild,left,mid);
	construct(rchild,mid+1,right);
	st[parent]=st[lchild]+st[rchild];
}
segtree a;
int main()
{
	a.initialize();
	cin >> a.n;
	for(int i=1;i<=a.n;i++)
		cin >> a.arr[i];
	a.construct(1,1,a.n);
	int q;
	cin >> q;
	while(q--)
	{
		int c;
		int left,right,value;
		cin >> c;
		if(c==1)
		{
			cin >> left >> right >> value;
			a.rangeadd(1,1,a.n,left,right,value);
		}
		else
		{
			cin >> left >> right;
			cout << a.rangesum(1,1,a.n,left,right) << "\n";
		}
	}
	return 0;
}

