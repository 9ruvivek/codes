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
      Reference: https://threads-iiith.quora.com/Centroid-Decomposition-of-a-Tree

******************************************************************************************************************************************/
#define N 100001
#define LOGN 17
#define INF 1000000000
int n,m;
int u,v;
set<int> adj[N];
int level[N],subsize[N],ancestor[N][LOGN],parent[N];
int ans[N][LOGN];
int white[N];
int cursize;
int t;
void dfs(int par,int anc,int lev)
{
	ancestor[par][0]=anc;
	level[par]=lev;
	for(set<int>::iterator it=adj[par].begin();it!=adj[par].end();it++)
		if(*it!=anc)
			dfs(*it,par,lev+1);
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
void dfs1(int par,int anc)
{
	subsize[par]=1;
	cursize++;
	for(set<int>::iterator it=adj[par].begin();it!=adj[par].end();it++)
	{
		if(*it!=anc)
		{
			dfs1(*it,par);
			subsize[par]+=subsize[*it];
		}
	}
}
int dfs2(int par,int anc)
{
	for(set<int>::iterator it=adj[par].begin();it!=adj[par].end();it++)
		if(*it!=anc && subsize[*it]>cursize/2)
			return dfs2(*it,par);
	return par;
}
void centroid_decomposition(int par,int anc)
{
	cursize=0;
	dfs1(par,par);
	int centroid=dfs2(par,par);
	if(!anc)
		anc=centroid;
	parent[centroid]=anc;
	for(set<int>::iterator it=adj[centroid].begin();it!=adj[centroid].end();it++)
	{
		adj[*it].erase(centroid);
		centroid_decomposition(*it,centroid);
	}
	adj[centroid].clear();
}
int dist(int u,int v)
{
	return level[u]+level[v]-2*level[LCA(u,v)];
}
void update(int v)
{
	white[v]=!white[v];
	int par=v,i=0;
	while(par!=parent[par])
	{
		ans[par][i]=((white[v])?(min(ans[par][i],dist(par,v))):INF);
		par=parent[par];
		i++;
	}
	ans[par][i]=((white[v])?(min(ans[par][i],dist(par,v))):INF);
}
int query(int v)
{
	int par=v,res=INF;
	while(par!=parent[par])
	{
		for(int i=0;i<LOGN;i++)
			res=min(res,ans[par][i]+dist(par,v));
		par=parent[par];
	}
	for(int i=0;i<LOGN;i++)
		res=min(res,ans[par][i]+dist(par,v));
	return res;
}
int main()
{
	std::ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	for(int i=0;i<N;i++)
		for(int j=0;j<LOGN;j++)
			ans[i][j]=INF;
	cin >> n;
	for(int i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	dfs(1,0,0);
	findancestors();
	centroid_decomposition(1,0);
	cin >> m;
	int res;
	while(m--)
	{
		cin >> t >> v;
		if(t==0)
			update(v);
		else
		{
			res=query(v);
			if(res==INF)
				res=-1;
			cout << res << "\n";
		}
	}
	return 0;
}
