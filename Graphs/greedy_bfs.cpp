#include <iostream>
#include <vector>
#include <limits>
#include <utility> 
using namespace std;

class Queue {
private:
    struct Node {
        pair<int, int> data; // (heurística, nodo)
        Node* next;
        Node(pair<int, int> value) : data(value), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(pair<int, int> value) {
        Node* newNode = new Node(value);
        if (front == nullptr) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    pair<int, int> pop() {
        if (front == nullptr) {
            return {-1, -1}; // O cualquier otro valor que indique un error
        }
        pair<int, int> poppedData = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return poppedData;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void printQueue() const {
        Node* current = front;
        while (current != nullptr) {
            cout << "(" << current->data.first << ", " << current->data.second << ") ";
            current = current->next;
        }
        cout << endl;
    }
};


class Graph {
private:
    int V; // Número de vértices
    vector<vector<pair<int, int>>> adj; // Lista de adyacencia (vértice, peso)
    vector<int> heuristic; // Vector heurístico

public:
    Graph(int V); 
    void addEdge(int v, int w, int weight); // agrega una arista con peso al grafo
    void setHeuristic(const vector<int>& h); // establece el vector heurístico
    void greedyBFS(int src, int goal); 

private:
    int minDistance(const vector<int>& dist, const vector<bool>& visited); // encuentra el vértice con la distancia mínima
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
    heuristic.resize(V);
}

void Graph::addEdge(int v, int w, int weight) {
    adj[v].emplace_back(w, weight);
    adj[w].emplace_back(v, weight); // Si el grafo es dirigido, eliminar esta línea
}

void Graph::setHeuristic(const vector<int>& h) {
    heuristic = h;
}

void Graph::greedyBFS(int src, int goal) {
    vector<bool> visited(V, false);
    Queue queue;

    queue.push({heuristic[src], src});

    while (!queue.isEmpty()) {
        auto current = queue.pop();
        int u = current.second;

        if (u == goal) {
            cout << "Reached goal: " << goal << endl;
            return;
        }

        if (!visited[u]) {
            visited[u] = true;
            cout << "Visiting node: " << u << endl;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                if (!visited[v]) {
                    queue.push({heuristic[v], v});
                }
            }
        }
    }

    cout << "Goal not reachable from source." << endl;
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

    vector<int> heuristic = {10, 8, 7, 6, 5, 4, 3, 2, 1}; // Ejemplo de heurística
    g.setHeuristic(heuristic);

    g.greedyBFS(0, 8);

    return 0;
}
