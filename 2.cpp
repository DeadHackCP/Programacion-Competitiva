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
char P[2<<10][2<<10];
queue<PII> q;

void bfs(int i, int j){
    q.push({i,j});
    while(!q.empty()){
        cout <<"start distance which should be 0 forever: "  << D[i][j] << endl;
        PII s = q.front(); 
        if (s.fi < 0 || s.fi >= N || s.se < 0 || s.se >= M || MAP[s.fi][s.se] == '#' || V[s.fi][s.se] || q.empty()) {q.pop();continue;}
        cout << s.fi << " " << s.se << endl;
        q.pop();
        V[s.fi][s.se] = true;
        q.push({s.fi+1,s.se});
        D[s.fi+1][s.se] = D[s.fi][s.se]+1;  
        q.push({s.fi-1,s.se});
        D[s.fi-1][s.se] = D[s.fi][s.se]+1;  
        q.push({s.fi,s.se+1});
        D[s.fi][s.se+1] = D[s.fi][s.se]+1;  
        q.push({s.fi,s.se-1});
        D[s.fi][s.se-1] = D[s.fi][s.se]+1;  
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
    cout << D[si][sj] << endl;
    return 0;
}