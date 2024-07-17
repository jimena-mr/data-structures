#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// imprime la matriz de distancias
void printMatrix(vector<vector<int>>& dist, int V) {
    cout << "Matriz de distancias más cortas entre todos los pares de vértices:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
}

// algoritmo de FW para encontrar las distancias mínimas
void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    // inicialización de la diagonal como 0 
    for (int i = 0; i < V; ++i)
        dist[i][i] = 0;

    // inicialización con las distancias conocidas del grafo
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (graph[i][j] != 0)
                dist[i][j] = graph[i][j];

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printMatrix(dist, V);
}


// algoritmo de Bellman Ford para encontrar las distancias mínimas
void bellmanFord(vector<vector<int>>& graph, int V, int source) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] != INT_MAX && dist[u] != INT_MAX &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Verificar ciclos negativos
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != INT_MAX && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                cout << "El grafo contiene un ciclo negativo.\n";
                return;
            }
        }
    }

    cout << "Distancias mínimas desde el vértice " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {

    /*
    int V;
    cout << "Ingrese el número de vértices del grafo: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    cout << "Ingrese la matriz de adyacencia del grafo (use 'INF' para representar la ausencia de conexión):\n";

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            string weight;
            cin >> weight;
            if (weight == "INF")
                graph[i][j] = INT_MAX; // representa infinito
            else
                graph[i][j] = stoi(weight); // Peso de la arista
        }
    }

    */
    vector<vector<int>> graph = {
        {0, 5, INT_MAX, 10},
        {INT_MAX, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int V = graph.size();

    floydWarshall(graph, V);

    // Ejemplo de uso de Bellman-Ford
    cout << "\nEjemplo de Bellman-Ford:\n";
    int source = 0; // Vértice fuente
    bellmanFord(graph, V, source);

}
