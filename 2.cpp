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
char MAP[2<<10][2<<10];
char V[2<<10][2<<10];
int D[2<<10][2<<10];
char Z[2<<10][2<<10];
PII P[2<<10][2<<10];
queue<PII> q;

void bfs(int i, int j){
    q.push({i,j});
    D[i][j] = 0;
    PII cases[4] = { {1,0}, {-1,0}, {0,1}, {0,-1}}; // U,D,R,L
    char moves[4] = {'D','U','R','L'};
    while(!q.empty()){
        PII s = q.front(); 
        q.pop();
        V[s.fi][s.se] = true;
        rep(k, 0, 4){
            int ni = cases[k].fi, nj = cases[k].se;
            ni += s.fi;
            nj += s.se;
            if (ni < 0 || ni >= N || nj < 0 || nj >= M || MAP[ni][nj] == '#' || MAP[ni][nj] == 'A' || V[ni][nj]) {
                continue;
            }
            V[ni][nj] = true;
            D[ni][nj] = D[s.fi][s.se] + 1;
            Z[ni][nj] = moves[k];
            P[ni][nj] = {s.fi, s.se};
            q.push({ni,nj});
        } 
    }
}

int main(){
    cin >> N >> M;
    cin.ignore();
    rep(i, 0, N){
        string cc;
        getline(cin, cc);
        rep(j, 0, M){
           MAP[i][j] = cc[j];
           if (cc[j] == 'A') {si = i; sj = j;}
           if (cc[j] == 'B') {ei = i; ej = j;}
        }
    }
    bfs(si, sj); 
    int res = D[ei][ej];
    if (res){
        if(D[ei][ej]){
            cout << "YES" << endl;
            cout << res << endl;
        }
        int ci = ei, cj = ej;
        string res2;
        per(i, 0, res){
            res2.pb(Z[ci][cj]);
            PII x = P[ci][cj];
            ci = x.fi;
            cj = x.se;
        }
        reverse(all(res2));
        cout << res2 << endl;
    } else{
        cout << "NO" << endl;
    } 
    return 0;
}