// Dijkstra version basica
#include <iostream>
#include <vector>
#include <limits>
using namespace std;


class Graph {
private:
    int V; // Número de vértices
    vector<vector<int>> adj; // Matriz de adyacencia

public:
    Graph(int V); // Constructor
    void addEdge(int v, int w, int weight); // Agrega una arista con peso al grafo
    void dijkstra(int src); // Algoritmo de Dijkstra (Versión Básica)

private:
    int minDistance(const vector<int>& dist, const vector<bool>& visited); // Encuentra el vértice con la distancia mínima
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V, vector<int>(V, 0));
}

void Graph::addEdge(int v, int w, int weight) {
    adj[v][w] = weight;
    adj[w][v] = weight; // Si el grafo es dirigido, eliminar esta línea
}

int Graph::minDistance(const vector<int>& dist, const vector<bool>& visited) {
    int min = numeric_limits<int>::max(), min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Graph::dijkstra(int src) {
    vector<int> dist(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && adj[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
    }

    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

int main() {
    Graph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.dijkstra(0);

    return 0;
}
