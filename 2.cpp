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

int N, M;
int si, sj;
int ei, ej;
// create the matrix that will hold the data of the map of the game
char MAP[2<<10][2<<10];
// create the matrix of the visited vertices
char V[2<<10][2<<10];   
// create the matrix of distance vertices
int D[2<<10][2<<10];
// create the matrix for label the movements
char Z[2<<10][2<<10];
// create the matrix for the parent pointers
PII P[2<<10][2<<10];
// create the queue for the bfs
queue<PII> q;

void bfs(int i, int j){
    // push the first or starter node that is being explored
    q.push({i,j});
    // set the first distance as zero
    D[i][j] = 0;
    // declare the cases for possible movements
    PII cases[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} }; // D,D,R,L
    // declare the label for the movements
    char moves[4] = {'D','U','R','L'};
    // do the search until the queue is empty
    while(!q.empty()){
        // take the first node based on the queue
        PII s = q.front(); q.pop();
        // set such node as visited
        V[s.fi][s.se] = true;
        // do the 4 possible movements for the current node being explored
        rep(k, 0, 4){
            // fetch the coordinates of the current position being explored
            int ni = cases[k].fi, nj = cases[k].se;
            // apply the movements on the node
            ni += s.fi;
            nj += s.se;
            // test that the node for being explored is not outside the constraints of the current map
            if (ni < 0 || ni >= N || nj < 0 || nj >= M || MAP[ni][nj] == '#' || MAP[ni][nj] == 'A' || V[ni][nj]) continue;
            // set the node as explored
            V[ni][nj] = true;
            // update the distance for such node
            D[ni][nj] = D[s.fi][s.se] + 1;
            // set the movement for such move being exerted
            Z[ni][nj] = moves[k];
            // set the parent pointer
            P[ni][nj] = {s.fi, s.se};
            // push the following node into the queue
            q.push({ni,nj});
        } 
    }
}

int main(){
    // enter the input
    cin >> N >> M;
    cin.ignore();
    // enter the matrix
    rep(i, 0, N){
        string cc;
        getline(cin, cc);
        rep(j, 0, M){
           MAP[i][j] = cc[j];
           // set the initial node
           if (cc[j] == 'A') {si = i; sj = j;}
           // set the end node
           if (cc[j] == 'B') {ei = i; ej = j;}
        }
    }
    // exert bfs on the first node
    bfs(si, sj); 
    // retrieve the minimum distance for such node
    int res = D[ei][ej];
    // if the solution exists then reconstruct the way tat was followed to get into the destination
    if (res){
        if(D[ei][ej]){
            cout << "YES" << endl;
            cout << res << endl;
        }
        int ci = ei, cj = ej;
        string res2;
        // reconstruct the path into words
        per(i, 0, res){
            res2.pb(Z[ci][cj]);
            PII x = P[ci][cj];
            ci = x.fi;
            cj = x.se;
        }
        // reverse it because the path was constructed into a a reverse way
        reverse(all(res2));
        // display the answer 
        cout << res2 << endl;
    } else{
        // if there is no way to get to the destination display "NO"
        cout << "NO" << endl;
    } 
    return 0;
}