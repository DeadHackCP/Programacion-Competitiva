#include <bits/stdc++.h>
using namespace std;

// declare variables for the size of the graph
int n, m;
// maximum size of the array
const int MXN = 1e5 + 1;
// inf value
const long long INF = 1e18;
// adjacency list for the vector
vector<pair<long long, int>> G[MXN];

// dijkstra module
long long dijkstra() {
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
    // the first parameter describes the nature of the elements contains the following
        // long long -> current distance (first one for proper ordering)
        // int -> current node
        // int -> flag indicating wether the coupon has been used
    // the second parameter describes the underlying container for the elements
        // basically a vector that holds the elements, which are tuples given by the expression tuple <long long, int, int>
    // the third parameter indicates the comparison function used to build up the minimum heap
        // it basically compares each element in cascade to order them
    // in this case the first element is the distance so the elements are going to be ordered based on their distances, so that the first element will always be the one with the minimum distance
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
    // the inital distance is zero
    dist[1][0] = 0;
    // push such node into it
        // distance : 0
        // node : 1
        // has the coupon been used? : 0 (no)
    pq.push({0, 1, 0}); 
    // while the queue isn't empty we iterate over its elements
    while (!pq.empty()) {
        // get the element at the top of the queue, which is the element represented by the minimum distance known
        auto [d, u, used] = pq.top();pq.pop();
        // if the node being processed is the same as the final node then stop the algorithm and returns the distance to such node
        if (u == n) return d; 
        // if the distance to the node being processed is greater than the distance to the same node but with the coupon been used skip the current iteration
        if (d > dist[u][used]) continue; 
        // for each adjacent node to the node being processed
        for (auto [cost, v] : G[u]) {
            // relaxation process for the path on which the coupon has been used   
            if (d + cost < dist[v][used]) {
                dist[v][used] = d + cost;
                pq.push({dist[v][used], v, used});
            }
            
            if (!used && d + (cost/2) < dist[v][1]) {
                dist[v][1] = d + (cost/2);
                pq.push({dist[v][1], v, 1});
            }
        }
    }
    
    return -1; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL_DEFINE
    freopen("entrada.txt", "rt", stdin);
    freopen("salida.txt", "wt", stdout);
    #endif
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        G[a].push_back({c, b});
    }
    
    cout << dijkstra() << '\n';
    
    return 0;
}