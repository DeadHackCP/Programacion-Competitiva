#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)

const int MAXN = 1024;
char MAP[MAXN][MAXN];
bool V[MAXN][MAXN];
int n, m;

void dfs(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || MAP[i][j] == '#' || V[i][j]) {
        return;
    }
    V[i][j] = true;
    dfs(i+1, j);
    dfs(i-1, j);
    dfs(i, j+1);
    dfs(i, j-1);
}

int main() {
    cin >> n >> m;
    cin.ignore();
    rep(i, 0, n) {
        string line;
        getline(cin, line);
        rep(j, 0, m) 
            MAP[i][j] = line[j];
    }
    int res = 0;
    rep(i, 0, n)
        rep(j, 0, m) {
            if (MAP[i][j] == '.' && !V[i][j]) {
                dfs(i, j);
                res++;
            }
        }
    cout << res << endl;
}