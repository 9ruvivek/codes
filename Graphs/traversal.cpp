/*************************************************************************************************************************************************
	
						     Author  : Vivek Nynaru
   						     Handle  : kevin11 
						     Year    :  2015
*************************************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;
#define SpeedUp std::ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

/************************************************************************************************************************************************
	Creating a basic utility for graph based sums
usage:
     let name of graph be test
     test.create(n);  To notify graph abt size as n
     test.ins(u,v);   To inform about a uni directional edge from u to v
     test.bfs(x);     To run a bfs from vertex x

*************************************************************************************************************************************************/

#define N 500
class Graph
{
   public:
	vector<int> adj[N];
	int parent[N];
	int dis[N];
	int n;
	bitset<N> vis;
	void create(int size);
	void ins(int u,int v);
	void bfs(int par);
};
void Graph::create(int size)
{
	n=size;
	vis.reset();
	for(int i=0;i<=n;i++)
	{
		adj[i].clear();
		parent[i]=0;
		dis[i]=1000000007;
	}
}
void Graph::ins(int u,int v)
{
	adj[u].push_back(v);
}
void Graph::bfs(int par)
{
	int child;
	queue<int> que;
	while(!que.empty())
		que.pop();
	dis[par]=0;
	vis.set(par);
	que.push(par);
	while(!que.empty())
	{
		par=que.front();
		que.pop();
		for(int i=0;i<adj[par].size();i++)
		{
			child=adj[par][i];
			if(!vis[child])
			{
				dis[child]=dis[par]+1;
				vis.set(child);
				parent[child]=par;
				que.push(child);
			}
		}
	}
}
int n,m,u,v;
Graph test;
int main()
{
	SpeedUp;
	//clock_t tStart = clock();
	//seive();         // Usage: ok[i]
	//totient();       // Usage: phi[i]
	//Fact();          // Usage: fact[i]
	//COMB();          // Usage: comb(a,b) or C[a][b]
        cin >> n >> m;
	test.create(n);
	for(int i=1;i<=m;i++)
	{
		cin >> u >> v;
		test.ins(u,v);
		test.ins(v,u);
	}
	test.bfs(1);
	for(int i=1;i<=n;i++)
		cout << i << " " << test.dis[i] << "\n";
	//exectime();
	return 0;
}
