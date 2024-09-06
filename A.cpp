#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 1000; 
int n, m;
int vx[] = {1, -1, 0, 0};
int vy[] = {0, 0, 1, -1};

bool valid(int x, int y) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

char cha(int hi, int hj, int pi, int pj) {
    if (pi > hi) return 'D';
    else if (pi < hi) return 'U';
    else if (hj > pj) return 'L';
    else return 'R';
}

pair<bool, string> bfs(vector<string> &G, int ipi, int jpj) {
    queue<pair<int,int>> monster, personaje;
    vector<vector<bool>> visM(n, vector<bool>(m, false)), visP(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> segui(n, vector<pair<int,int>>(m, {-1,-1}));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (G[i][j] == 'M') {
                monster.push({i,j});
                visM[i][j] = true;
            } else if (G[i][j] == 'A') {
                personaje.push({i,j});
                visP[i][j] = true;
            }
        }
    }

    bool f = false;
    int ii = ipi, jj = jpj;

    while (!personaje.empty() && !f) {
        int size_m = monster.size();
        while (size_m--) {
            auto pM = monster.front();
            monster.pop();
            for (int i = 0; i < 4; i++) {
                int xm = pM.first + vy[i], ym = pM.second + vx[i];
                if (valid(xm, ym) && G[xm][ym] != '#' && !visM[xm][ym]) {
                    visM[xm][ym] = true;
                    monster.push({xm, ym});
                }
            }
        }

        int size_p = personaje.size();
        while (size_p-- && !f) {
            auto pP = personaje.front();
            personaje.pop();
            if (pP.first == 0 || pP.first == n-1 || pP.second == 0 || pP.second == m-1) {
                f = true;
                ii = pP.first;
                jj = pP.second;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int xp = pP.first + vy[i], yp = pP.second + vx[i];
                if (valid(xp, yp) && G[xp][yp] != '#' && !visM[xp][yp] && !visP[xp][yp]) {
                    visP[xp][yp] = true;
                    personaje.push({xp, yp});
                    segui[xp][yp] = pP;
                }
            }
        }
    }

    string s = "";
    if (f) {
        while (ii != ipi || jj != jpj) {
            auto prev = segui[ii][jj];
            s += cha(prev.first, prev.second, ii, jj);
            ii = prev.first;
            jj = prev.second;
        }
        reverse(s.begin(), s.end());
    }
    return {f, s};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL_DEFINE
    freopen("entrada.txt", "rt", stdin);
    freopen("salida.txt", "wt", stdout);
    #endif
    cin >> n >> m;
    vector<string> G(n);
    for (int i = 0; i < n; i++) cin >> G[i];

    int ii, jj;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (G[i][j] == 'A') {
                ii = i;
                jj = j;
                break;
            }
        }
        if (G[i][jj] == 'A') break;
    }

    auto [f, str] = bfs(G, ii, jj);
    if (f) {
        cout << "YES\n";
        cout << str.size() << '\n';
        cout << str << '\n';
    } else {
        cout << "NO\n";
    }
    return 0;
}