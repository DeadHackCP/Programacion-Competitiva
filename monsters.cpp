#include <bits/stdc++.h>
using namespace std;

// limit of the graph size
const int MAX_SIZE = 1000; 
// actual size of the graph
int n, m;
// possible movements
int vx[] = {1, -1, 0, 0};
int vy[] = {0, 0, 1, -1};

// check if the positon being explored is valid or within the constraints of the problem
bool valid(int x, int y) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

// map the movement to characters or expressions
char cha(int hi, int hj, int pi, int pj) {
    if (pi > hi) return 'D';
    else if (pi < hi) return 'U';
    else if (hj > pj) return 'L';
    else return 'R';
}


// breadh first search, it will return the path in words plus a boolean
pair<bool, string> bfs(vector<string> &G, int ipi, int jpj) {
    // a queue for each one, player and all the monsters
    queue<pair<int,int>> monster, personaje;
    // vector with n vectors of m booleans, all settled to false
        // visM -> for the monster
        // visP -> for the player
    vector<vector<bool>> visM(n, vector<bool>(m, false)), visP(n, vector<bool>(m, false));
    // vector of vectors that contains pairs of integers. It will be the parent pointer structure
        // n vectors of m pairs
        // each pair is settled as {-1, -1}
    vector<vector<pair<int,int>>> segui(n, vector<pair<int,int>>(m, {-1,-1}));
    // traverse the whole graph, setting as visited by player its initial position, and doing the same for each monster
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (G[i][j] == 'M') {
                // adding the position of the monster to the monster's queue
                monster.push({i,j});
                visM[i][j] = true;
            } else if (G[i][j] == 'A') {
                // adding the position of the player to the player's queue
                personaje.push({i,j});
                visP[i][j] = true;
            }
        }
    }
    bool f = false;
    // setting starter position
    int ii = ipi, jj = jpj;

    // while personaje queue isn't empty and it hasn't reached any of the limits of the graph
    while (!personaje.empty() && !f) {
        // retrieve amount of monsters positions
        int size_m = monster.size();
        // apply every possible movement to all monsters
        while (size_m--) {
            // take the monster from the front of the queue
            auto pM = monster.front();
            // pop such monster's position
            monster.pop();
            // apply each possible movement to such monster's position
            for (int i = 0; i < 4; i++) {
                // exert the movement
                int xm = pM.first + vy[i], ym = pM.second + vx[i];
                // verify if the position is still within the graph or it isn't a wall or it wasnt' visited by another monster previously
                if (valid(xm, ym) && G[xm][ym] != '#' && !visM[xm][ym]) {
                    // set it as visited
                    visM[xm][ym] = true;
                    // push the new position so it will be further explored later
                    monster.push({xm, ym});
                }
            }
        }
        // --> once all monsters have done their one-step possible movements, do the same with the player
        int size_p = personaje.size();
        // for each possible movement of the player based on the positions that it has at the moment and any limit was reached at the moment
        while (size_p-- && !f) {
            // take the front of the queue
            auto pP = personaje.front();
            // pop it
            personaje.pop();
            // if the player reached a limit of the map, there's a possible way for him to scape so end the loop
            if (pP.first == 0 || pP.first == n-1 || pP.second == 0 || pP.second == m-1) {
                f = true;
                // update the starter position to the win position
                ii = pP.first;
                jj = pP.second;
                break;
            }
            // exert every possible movement of such position
            for (int i = 0; i < 4; i++) {
                int xp = pP.first + vy[i], yp = pP.second + vx[i];
                // verify that it doesn't violate any constraint or condition
                    // -> the cell mustn't being visited priorly by any monster
                if (valid(xp, yp) && G[xp][yp] != '#' && !visM[xp][yp] && !visP[xp][yp]) {
                    // set it as visited
                    visP[xp][yp] = true;
                    // push the new position so it'll be explored later
                    personaje.push({xp, yp});
                    // set the parent pointer, remembar that pP is a pair<int,int> that holds the positon being explored
                    segui[xp][yp] = pP;
                }
            }
        }
    }
    // once the bfs has terminated we have to build the path
    string s = "";
    // if the player achieved a succesful escape
    if (f) {
        // while the starter position isn't reached
        while (ii != ipi || jj != jpj) {
            // retrieve the prior position 
            auto prev = segui[ii][jj];
            // map such position to a character and add it to the string
            s += cha(prev.first, prev.second, ii, jj);
            // update the position
            ii = prev.first;
            jj = prev.second;
        }
        // finally reverse the string, since the path has been built backwards
        reverse(s.begin(), s.end());
    }
    // return the boolean and the reconstructed path
    return {f, s};
}

int main() {
    // microptimizations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL_DEFINE
    freopen("entrada.txt", "rt", stdin);
    freopen("salida.txt", "wt", stdout);
    #endif
    // entering of the number of rows and columns
    cin >> n >> m;
    // vector for "n" strings
    vector<string> G(n);
    // entering each line into the vector
    for (int i = 0; i < n; i++) cin >> G[i];
    // declaring starter position (player)
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
    // do bfs on the player position
        // G -> Graph
        // ii -> player position on "x" axis
        // jj -> player position on "y" axis
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