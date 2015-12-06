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
      
      Question: Find LCA

      Complexity: O(Nlog(N))

******************************************************************************************************************************************/
#define MAXN 200005
#define LOGMAXN 20
int n,m;
int u,v;
int parent[MAXN];
vi adj[MAXN];
bitset<MAXN> vis;
int level[MAXN];
int ancestor[MAXN][LOGMAXN];
int q;
// n nodes, m edges, u is parent of v
void dfs(int par,int lev)
{
	if(!vis[par])
	{
		vis.set(par);
		level[par]=lev;
		for(int i=0;i<adj[par].size();i++)
			dfs(adj[par][i],lev+1);
	}
}
void findancestors()
{
	for(int i=1;i<=n;i++)
		for(int j=0;(1<<j)<n;j++)
			ancestor[i][j]=0;
	for(int i=1;i<=n;i++)
		ancestor[i][0]=parent[i];
	for(int j=1;(1<<j)<n;j++)
		for(int i=1;i<=n;i++)
			if(ancestor[i][j-1]!=0)
				ancestor[i][j]=ancestor[ancestor[i][j-1]][j-1];
}
int lca(int p,int q)
{
	int log;
	if(level[p]<level[q])
		swap(p,q);
	for(log=1;(1<<log)<=level[p];log++);
	log--;
	for(int i=log;i>=0;i--)
		if(level[p]-(1<<i)>=level[q])
			p=ancestor[p][i];
	if(p==q)
		return p;
	for(int i=log;i>=0;i--)
		if(ancestor[p][i]!=0 && ancestor[p][i]!=ancestor[q][i])
			p=ancestor[p][i],q=ancestor[q][i];
	return parent[p];
}
int main()
{
	cin >> n >> m;
	for(int i=0;i<m;i++)
	{
		cin >> u >> v;
		parent[v]=u;
		adj[u].pb(v);
	}
	dfs(1,1);
	findancestors();
	cin >> q;
	while(q--)
	{
		cin >> u >> v;
		cout << lca(u,v) << "\n";
	}
	return 0;
}

