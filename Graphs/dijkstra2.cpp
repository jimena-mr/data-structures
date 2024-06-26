// dijsktra guardando el padre
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
    void dijkstraWithParent(int src);

private:
    int minDistance(const vector<int>& dist, const vector<bool>& visited); // Encuentra el vértice con la distancia mínima
    void printPath(const vector<int>& parent, int j); // Imprime el camino desde el nodo fuente hasta j
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

void Graph::printPath(const vector<int>& parent, int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    cout << j << " ";
}

void Graph::dijkstraWithParent(int src) {
    vector<int> dist(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (!visited[v] && adj[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
    }

    cout << "Vertex \t Distance from Source \t Path" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " \t\t " << dist[i] << " \t\t\t " << src << " ";
        printPath(parent, i);
        cout << endl;
    }
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

    g.dijkstraWithParent(0);

    return 0;
}
