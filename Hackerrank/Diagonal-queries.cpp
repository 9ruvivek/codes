/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/******************************************************************************************************************************************
      
      Question: https://www.hackerrank.com/contests/w15/challenges/diagonal-queries

******************************************************************************************************************************************/
#define N 1000001
#define NLOGN 20000001
#define MOD 1000000007

ll arr[2*N];
class segtree
{
	public:
		ll st[NLOGN];
		ll lazya[NLOGN];
		ll lazyd[NLOGN];
		void initialize();
		void construct(ll parent,ll left,ll right);
		void rangeadd(ll parent,ll start,ll end,ll left,ll right,ll a,ll d);
		ll rangesum(ll parent,ll start,ll end,ll left,ll right);

};
void segtree::initialize()
{
	for(int i=0;i<NLOGN;i++)
		st[i]=lazya[i]=lazyd[i]=0ll;
}
void segtree::rangeadd(ll parent,ll start,ll end,ll left,ll right,ll a,ll d)
{
	// For each node try to get initial term,difference so that things go easy 
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(start+end)>>1;
	ll len=end-start+1;
	if(lazyd[parent] || lazya[parent])
	{
		st[parent]+=((len*lazya[parent])%MOD)+(((((len*(len-1))/2)%MOD)*lazyd[parent])%MOD);
		st[parent]%=MOD;
		if(len>1)
		{
			lazya[lchild]+=lazya[parent];
			lazya[lchild]%=MOD;

			lazyd[lchild]+=lazyd[parent];
			lazyd[lchild]%=MOD;

			lazya[rchild]+=lazya[parent]+(((mid+1-start)*lazyd[parent])%MOD);
			lazya[rchild]%=MOD;

			lazyd[rchild]+=lazyd[parent];
			lazyd[rchild]%=MOD;
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
		st[parent]+=((l1-l2)*a)%MOD;
		st[parent]%=MOD;
		st[parent]+=((((((((l1*(l1-1))/2)%MOD)-(((l2*(l2-1))/2)%MOD))%MOD)+MOD)%MOD)*d)%MOD;
		st[parent]%=MOD;
		if(len>1)
		{
			lazya[lchild]+=(a+(start-left)*d)%MOD;
			lazya[lchild]%=MOD;

			lazyd[lchild]+=d;
			lazyd[lchild]%=MOD;

			lazya[rchild]+=a+(((mid-left+1)*d)%MOD)%MOD;
			lazya[rchild]%=MOD;

			lazyd[rchild]+=d;
			lazyd[rchild]%=MOD;
		}
		return;
	}
	rangeadd(lchild,start,mid,left,right,a,d);
	rangeadd(rchild,mid+1,end,left,right,a,d);
	st[parent]=(st[lchild]+st[rchild])%MOD;
	return;
}
ll segtree::rangesum(ll parent,ll start,ll end,ll left,ll right)
{
	ll lchild=parent<<1;
	ll rchild=lchild+1;
	ll mid=(start+end)>>1;
	ll len=end-start+1;
	if(lazyd[parent] || lazya[parent])
	{
		st[parent]+=((len*lazya[parent])%MOD)+(((((len*(len-1))/2)%MOD)*lazyd[parent])%MOD);
		st[parent]%=MOD;
		if(len>1)
		{
			lazya[lchild]+=lazya[parent];
			lazya[lchild]%=MOD;

			lazyd[lchild]+=lazyd[parent];
			lazyd[lchild]%=MOD;

			lazya[rchild]+=lazya[parent]+(((mid+1-start)*lazyd[parent])%MOD);
			lazya[rchild]%=MOD;

			lazyd[rchild]+=lazyd[parent];
			lazyd[rchild]%=MOD;
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
	return (lsum+rsum)%MOD;
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
segtree rsum;
ll n,m,q,tot;
string type;
ll ptr,val;
ll X1,X2,Y1,Y2;
ll lptr,rptr;
ll a,d;
int main()
{
	std::ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	cin >> n >> m >> q;
	tot=n+m-1;
	while(q--)
	{
		cin >> type;
		if(type=="Qr")
		{
			cin >> ptr >> val;
			ll start=n-ptr+1;
			ll end=n-ptr+m;
			a=val%MOD;
			a=(a+MOD)%MOD;
			d=val%MOD;
			d=(d+MOD)%MOD;
			rsum.rangeadd(1,1,tot,start,end,a,d);
		}
		else if(type=="Qc")
		{
			cin >> ptr >> val;
			ll start=n-n+ptr;
			ll end=n-1+ptr;
			a=(n*val)%MOD;
			a=(a+MOD)%MOD;
			d=(-val)%MOD;
			d=(d+MOD)%MOD;
			rsum.rangeadd(1,1,tot,start,end,(n*val)%MOD,(MOD-val)%MOD);
		}
		else if(type=="Qs")
		{
			cin >> X1 >> Y1 >> X2 >> Y2 >> val;
			ll lstart,lend;
			ll rstart,rend;
			ll cnt;
			lstart=n-X2+Y1;
			rend=n-X1+Y2;
			cnt=min(X2-X1,Y2-Y1);
			lend=lstart+cnt-1;
			rstart=rend-cnt+1;
			if(lstart<=lend)
			{
				a=val%MOD;
				a=(a+MOD)%MOD;
				d=val%MOD;
				d=(d+MOD)%MOD;
				rsum.rangeadd(1,1,tot,lstart,lend,a,d);
			}
			if(rstart<=rend)
			{
				a=(cnt*val)%MOD;
				a=(a+MOD)%MOD;
				d=(-val)%MOD;
				d=(d+MOD)%MOD;
				rsum.rangeadd(1,1,tot,rstart,rend,(cnt*val)%MOD,(MOD-val)%MOD);
			}
			if(lend+1<=rstart-1)
			{
				a=((cnt+1)*val)%MOD;
				a=(a+MOD)%MOD;
				d=0ll;
				rsum.rangeadd(1,1,tot,lend+1,rstart-1,a,d);
			}
		}
		else
		{
			cin >> lptr >> rptr;
			cout << rsum.rangesum(1,1,tot,lptr,rptr) << "\n";
		}
	}
	return 0;
}
