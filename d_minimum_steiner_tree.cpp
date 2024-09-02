#include<iostream>
#include<vector>
#include<cassert>
using namespace std;
// declare the following variables
// N -> number of vertices numbered from 1 to N
// K -> number of vertices that we want to preserve
int N,K;
// Adjecency list
vector<int>G[2<<17];
// Visited array
bool V[2<<17];
// Depth first search algorithm
int dfs(int u,int p)
{
    // declare a variable that does somethin?
	int ret=0;
    // 'f' indicate if 'u' vertex wether visitted or not
	bool f=V[u];
    // process each adjacent vertex to u in such way that it doesn't revisit its parent or the vertex from which it's comming
	for(int v:G[u])if(v!=p)
	{
        // continue exploring the branch
		int t=dfs(v,u);
        // the amount of visited nodes increase by how many vere involved to get to any of the desired ones
		ret+=t;
        // If in this way any of the desired vertices was found set the current vertex as visited so it will be considered as one of the neccessary ones on the "prior" iteration
		if(t)f=true;
	}
    // for the case on which we get until the last element of a branch we'll just increment ret by one if 'f' is one of the desired vertices to preserve
	if(f)ret++;
    // return ret
	return ret;
}
int main()
{
    // uncesseray mircro-optimizations
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    // entering the number of edges and the number of vertices to be preserved
	cin>>N>>K;
    // processing each edge
	for(int i=1;i<N;i++)
	{
        // entering each edge and mapping it into a position
            // since node's names range from 1 to N, then we map them to 0 to N-1 to match them with typical array positions
		int a,b;cin>>a>>b;a--,b--;
        // registering the edge into the adjacency list
		G[a].push_back(b);
		G[b].push_back(a);
	}
    // create the root variable
	int root;
    // processing each of the vertices to be preserved
	for(int i=0;i<K;i++)
	{
        // save each of the K vertices as a root
		cin>>root;
        // map it to an array position
		root--;
        // establish such index as visited
		V[root]=true;
	}
    // Exert dfs on root with parameter p = -1
	cout<<dfs(root,-1)<<endl;
}
