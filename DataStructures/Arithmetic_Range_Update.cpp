/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: Increasing Range Update and query
      updates range with values a val,2*val,3*val,.......

******************************************************************************************************************************************/
#define N 1000001
#define NLOGN 20000001
class segtree
{
	public:
		ll n;
		ll arr[N];
		ll st[NLOGN];
		ll lazya[NLOGN];
		ll lazyd[NLOGN];
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
		st[i]=lazya[i]=lazyd[i]=0ll;
}
void segtree::rangeadd(ll parent,ll start,ll end,ll left,ll right,ll value)
{
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(start+end)>>1;
	ll len=end-start+1;
	if(lazyd[parent])
	{
		st[parent]+=len*lazya[parent]+((len*(len-1))/2)*lazyd[parent];
		if(len>1)
		{
			lazya[lchild]+=lazya[parent];
			lazyd[lchild]+=lazyd[parent];
			lazya[rchild]+=lazya[parent]+(mid+1-start)*lazyd[parent];
			lazyd[rchild]+=lazyd[parent];
		}
		lazya[parent]=0ll;
		lazyd[parent]=0ll;
	}
	if(start>end || start>right || end<left)
		return;
	if(start>=left && end<=right)
	{
		ll l1=end-left+1;
		ll l2=start-left;
		st[parent]+=(((l1*(l1+1))/2)-((l2*(l2+1))/2))*value;
		if(len>1)
		{
			lazya[lchild]+=(start-left+1)*value;
			lazyd[lchild]+=value;
			lazya[rchild]+=(mid-left+2)*value;
			lazyd[rchild]+=value;
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
	if(lazyd[parent])
	{
		st[parent]+=len*lazya[parent]+((len*(len-1))/2)*lazyd[parent];
		if(len>1)
		{
			lazya[lchild]+=lazya[parent];
			lazyd[lchild]+=lazyd[parent];
			lazya[rchild]+=lazya[parent]+(mid+1-start)*lazyd[parent];
			lazyd[rchild]+=lazyd[parent];
		}
		lazya[parent]=0ll;
		lazyd[parent]=0ll;
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
