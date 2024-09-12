#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5; // Máximo número de nodos (ajustar según el problema)
vector<int> adj[MAXN];    // Lista de adyacencia para representar el grafo
bool vis[MAXN];           // Array para marcar nodos visitados
int dist[MAXN];           // Array para almacenar distancias desde el nodo inicial

void bfs(int start) {
    queue<int> q;
    q.push(start);        // Añadir nodo inicial a la cola
    vis[start] = true;    // Marcar nodo inicial como visitado
    dist[start] = 0;      // Distancia al nodo inicial es 0

    while (!q.empty()) {
        int v = q.front(); q.pop();  // Obtener y remover el primer nodo de la cola
        
        // Explorar todos los vecinos del nodo actual
        for (int u : adj[v]) {
            if (!vis[u]) {           // Si el vecino no ha sido visitado
                vis[u] = true;       // Marcarlo como visitado
                dist[u] = dist[v] + 1; // Su distancia es la del nodo actual + 1
                q.push(u);           // Añadirlo a la cola para exploración futura
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  // Optimizaciones de E/S para competencias

    int n, m; // n: número de nodos, m: número de aristas
    cin >> n >> m;

    // Leer las aristas y construir el grafo
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a); // Eliminar esta línea si el grafo es dirigido
    }

    bfs(1); // Iniciar BFS desde el nodo 1 (ajustar si es necesario)

    // Imprimir las distancias desde el nodo inicial a todos los demás
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << "\n";

    return 0;
}
