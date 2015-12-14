/**********************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015

**********************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
typedef vector < int > vi;
#define pb push_back

/******************************************************************************************************************************************
      
      Question: Find maximum weight in a path from u to v

******************************************************************************************************************************************/
#define N 10001
#define LOGN 14
#define NLOGN 140001
int tc;
int n;
int u,v,w;
vi adj[N],weight[N],edgeindex[N];
int otherend[N];
int level[N],subsize[N],ancestor[N][LOGN];
int size;
int chainnum,chainhead[N],chainidx[N],arridx[N];
int arr[N],st[NLOGN];
string type;
void dfs(int par,int anc,int lev)
{
	ancestor[par][0]=anc;
	level[par]=lev;
	subsize[par]=1;
	for(int i=0;i<adj[par].size();i++)
	{
		int child=adj[par][i];
		if(child!=anc)
		{
			otherend[edgeindex[par][i]]=child;
			dfs(child,par,lev+1);
			subsize[par]+=subsize[child];
		}
	}
}
void findancestors()
{
	for(int j=1;j<LOGN;j++)
		for(int i=1;i<=n;i++)
			if(ancestor[i][j-1])
				ancestor[i][j]=ancestor[ancestor[i][j-1]][j-1];
}
int LCA(int u,int v)
{
	if(level[u]<level[v])
		swap(u,v);
	int diff=level[u]-level[v];
	for(int i=0;i<LOGN;i++)
	{
		if(diff&1)
			u=ancestor[u][i];
		diff>>=1;
	}
	if(u==v)
		return u;
	for(int i=LOGN-1;i>=0;i--)
		if(ancestor[u][i]!=ancestor[v][i])
			u=ancestor[u][i],v=ancestor[v][i];
	return ancestor[u][0];
}
void build(int par,int start,int end)
{
	if(start==end)
	{
		st[par]=arr[start];
		return;
	}
	int lchild=par<<1;
	int rchild=lchild|1;
	int mid=(start+end)>>1;
	build(lchild,start,mid);
	build(rchild,mid+1,end);
	st[par]=max(st[lchild],st[rchild]);
}
void update(int par,int start,int end,int idx,int val)
{
	if(start>idx || end<idx)
		return;
	if(start==idx && start==end)
	{
		st[par]=val;
		arr[idx]=val;
		return;
	}
	int lchild=par<<1;
	int rchild=lchild|1;
	int mid=(start+end)>>1;
	update(lchild,start,mid,idx,val);
	update(rchild,mid+1,end,idx,val);
	st[par]=max(st[lchild],st[rchild]);
}
int query(int par,int start,int end,int left,int right)
{
	if(start>right || end<left)
		return 0;
	if(start>=left && end<=right)
		return st[par];
	int lchild=par<<1;
	int rchild=lchild|1;
	int mid=(start+end)>>1;
	int lq=query(lchild,start,mid,left,right);
	int rq=query(rchild,mid+1,end,left,right);
	return max(lq,rq);
}
void HLD(int par,int anc,int cost)
{
	if(!chainhead[chainnum])
		chainhead[chainnum]=par;
	chainidx[par]=chainnum;
	arridx[par]=size;
	arr[size++]=cost;
	int schild=0,scost,child;
	for(int i=0;i<adj[par].size();i++)
	{
		child=adj[par][i];
		if(child!=anc && (!schild || subsize[schild]<subsize[child]))
			schild=child,scost=weight[par][i];
	}
	if(schild)
		HLD(schild,par,scost);
	for(int i=0;i<adj[par].size();i++)
	{
		child=adj[par][i];
		if(child!=anc && child!=schild)
		{
			chainnum++;
			HLD(child,par,weight[par][i]);
		}
	}
	
}
int query_up(int u,int v)
{
	int uchain=chainidx[u],vchain=chainidx[v],res=0,head;
	while(uchain!=vchain)
	{
		head=chainhead[uchain];
		res=max(res,query(1,1,n,arridx[head],arridx[u]));
		u=ancestor[head][0];
		uchain=chainidx[u];
	}
	res=max(res,query(1,1,n,arridx[v],arridx[u]));
	return res;
}
int change(int idx,int w)
{
	idx=arridx[otherend[idx]];
	arr[idx]=w;
	update(1,1,n,idx,w);
}
int query_max(int u,int v)
{
	int lca=LCA(u,v);
	return max(query_up(u,lca),query_up(v,lca));
}
int main()
{
	cin >> tc;
	while(tc--)
	{
		size=1;
		chainnum=1;
		for(int i=0;i<N;i++)
		{
			adj[i].clear();
			weight[i].clear();
			edgeindex[i].clear();
			level[i]=0;
			subsize[i]=0;
			otherend[i]=0;
			chainhead[i]=0;
			chainidx[i]=0;
			arridx[i]=0;
			arr[i]=0;
			for(int j=0;j<LOGN;j++)
				ancestor[i][j]=0;
		}
		for(int i=0;i<NLOGN;i++)
			st[i]=0;
		cin >> n;
		for(int i=1;i<n;i++)
		{
			cin >> u >> v >> w;
			adj[u].pb(v);
			adj[v].pb(u);
			weight[u].pb(w);
			weight[v].pb(w);
			edgeindex[u].pb(i);
			edgeindex[v].pb(i);
		}
		dfs(1,0,0);
		findancestors();
		HLD(1,0,0);
		build(1,1,n);
		while(1)
		{
			cin >> type;
			if(type[0]=='D')
				break;
			cin >> u >> v;
			if(type[0]=='C')
				change(u,v);
			else
				cout << query_max(u,v) << "\n";
		}
	}
}
