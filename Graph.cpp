#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

class Grafo {
private:
    vector<vector<pair<int, int>>> adjList;
    int numVertices;

public:
    Grafo(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Añadir arista al grafo
    void addEdge(int u, int v, int peso) {
        adjList[u].push_back({v, peso});
        adjList[v].push_back({u, peso});  // Si el grafo es dirigido, elimina esta línea
    }

    // Imprimir el grafo
    void printGraph() {
        for (int i = 0; i < numVertices; ++i) {
            cout << "Nodo " << i << " conecta con: ";
            for (auto& vecino : adjList[i]) {
                cout << "(" << vecino.first << ", peso: " << vecino.second << ") ";
            }
            cout << endl;
        }
    }

    // DFS
    void DFS(int start) {
        vector<bool> visitado(numVertices, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int nodo = s.top();
            s.pop();

            if (!visitado[nodo]) {
                cout << nodo << " ";
                visitado[nodo] = true;
            }

            for (auto& vecino : adjList[nodo]) {
                if (!visitado[vecino.first]) {
                    s.push(vecino.first);
                }
            }
        }
        cout << endl;
    }

    // BFS
    void BFS(int start) {
        vector<bool> visitado(numVertices, false);
        queue<int> q;

        visitado[start] = true;
        q.push(start);

        while (!q.empty()) {
            int nodo = q.front();
            cout << nodo << " ";
            q.pop();

            for (auto& vecino : adjList[nodo]) {
                if (!visitado[vecino.first]) {
                    visitado[vecino.first] = true;
                    q.push(vecino.first);
                }
            }
        }
        cout << endl;
    }

    // Dijkstra
    void Dijkstra(int start) {
        vector<int> dist(numVertices, numeric_limits<int>::max());
        dist[start] = 0;

        auto compare = [&dist](int lhs, int rhs) {
            return dist[lhs] > dist[rhs];
        };
        priority_queue<int, vector<int>, decltype(compare)> pq(compare);

        pq.push(start);

        while (!pq.empty()) {
            int nodo = pq.top();
            pq.pop();

            for (auto& vecino : adjList[nodo]) {
                int v = vecino.first;
                int peso = vecino.second;

                if (dist[nodo] + peso < dist[v]) {
                    dist[v] = dist[nodo] + peso;
                    pq.push(v);
                }
            }
        }

        cout << "Distancias desde el nodo " << start << ":" << endl;
        for (int i = 0; i < numVertices; ++i) {
            cout << "Nodo " << i << " - Distancia: " << dist[i] << endl;
        }
    }
};

int main() {
    Grafo g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 3);

    cout << "Grafo:" << endl;
    g.printGraph();

    cout << "\nDFS desde el nodo 0:" << endl;
    g.DFS(0);

    cout << "\nBFS desde el nodo 0:" << endl;
    g.BFS(0);

    cout << "\nDijkstra desde el nodo 0:" << endl;
    g.Dijkstra(0);

    return 0;
}
