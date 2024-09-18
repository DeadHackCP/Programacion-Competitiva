#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937_64 mrand(random_device{}());
const ll mod=1000000007;
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

// maximum size of the array
const int MSIZE = 1e5+1;

const long long INF = 1e18; // declare the correct type of variables is super important!!

// declare variables for the size of the graph
int n, m;

// adjacency list
vector<pair<ll, int>> G[MSIZE]; // a vector on which each cell is a vector that holds pairs of long long and integers

// we don't need to pass any parameters since the adjacency list is declared as a global variable, the start node is always "1" and the end node is always "n"
ll dijkstra(){
    // declare a vector for the distances given that the vector has n + 1 elemnts (the vertices, labeling from 1 to n), and each one of the vertices are described by two labels, the first one is the distance to get to such vertex and the second is the distance, but beign that the coupon has been used
    vector<vector<ll>> dist(n+1, vector<ll>(2, INF));
// the first parameter describes the nature of the elements contains the following
        // long long -> current distance (first one for proper ordering)
        // int -> current node
        // int -> flag indicating wether the coupon has been used
    // the second parameter describes the underlying container for the elements
        // basically a vector that holds the elements, which are tuples given by the expression tuple <long long, int, int>
    // the third parameter indicates the comparison function used to build up the minimum heap
        // it basically compares each element in cascade to order them
    // in this case the first element is the distance so the elements are going to be ordered based on their distances, so that the first element will always be the one with the minimum distance
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
    // the inital distance is zero
    dist[1][0] = 0;
    // push such node into it
        // distance : 0
        // node : 1
        // has the coupon been used? : 0 (no)
    pq.push({0,1,0});
    // while the queue isn't empty we iterate over its elements
    while (!pq.empty()){
        // get the element at the top of the queue, which is the element represented by the minimum distance known
        auto [d, u, used] = pq.top(); pq.pop();
        // if the node being processed is the same as the final node then stop the algorithm and returns the distance to such node, because the final node's degree is zero, it doesn't have any edges to any other node (due to the problem statement)
        if (u == n) return d;
        // if the distance to the node being processed is greater than the distance to the same node but with the coupon been used skip the current iteration
            // this could happen if the algorithm finds a shorter path to the current node at some time, and in consequence dist[u][used] is less than the one that was declared at the first time  
        if (d > dist[u][used]) continue;
        for(auto [cost, v]: G[u]){
            // relaxation for the current state
            if (dist[v][used] > d + cost){
                dist[v][used] = d + cost;
                pq.push({dist[v][used], v, used});
            }
            // relaxation on the case that the coupon hasn't been used
            if(!used && dist[v][1] > d + (cost/2)){
                dist[v][1] = d + (cost/2);
                pq.push({dist[v][1], v, 1});
            }
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int a, b; ll c;
    rep(i, 0, m){
        cin >>  a >> b >> c;
        G[a].pb({c, b});
    }

    cout << dijkstra() << endl;
    return 0;   
}

