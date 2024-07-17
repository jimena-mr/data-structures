#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };
    Node* top;
public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            return -1; // O cualquier otro valor que indique un error
        }
        int poppedData = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return poppedData;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void printStack() const {
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
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

    void push(int value) {
        Node* newNode = new Node(value);
        if (front == nullptr) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int pop() {
        if (front == nullptr) {
            return -1; // O cualquier otro valor que indique un error
        }
        int poppedData = front->data;
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
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

class List {
private:
    vector<int> elements;

public:
    void push_back(int value) {
        elements.push_back(value);
    }

    vector<int>::iterator begin() {
        return elements.begin();
    }

    vector<int>::iterator end() {
        return elements.end();
    }
};

class Graph {
private:
    int V; // número de vértices
    vector<List> adj; // lista de adyacencia

public:
    Graph(int V); 
    void addEdge(int v, int w); // agrega una arista al grafo
    void BFS(int s);
    void DFS(int s);
    int BFSUtil(int start); // función auxiliar para BFS que encuentra el ciclo más corto desde un nodo
    void DFSUtil(int v, vector<bool>& visited); // Función auxiliar para DFS
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Agrega w a la lista de v
}

void Graph::BFS(int s) {
    vector<bool> visited(V, false);
    Queue queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.isEmpty()) {
        s = queue.pop();
        cout << s << " ";

        for (auto adjVertex : adj[s]) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }
    cout << endl;
}
int Graph::BFSUtil(int start) {
    vector<int> dist(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);
    Queue queue;

    dist[start] = 0;
    queue.push(start);

    while (!queue.isEmpty()) {
        int u = queue.pop();

        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = *it;

            if (dist[v] == numeric_limits<int>::max()) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue.push(v);
            } else if (parent[u] != v && parent[v] != u) {
                return dist[u] + dist[v] + 1;
            }
        }
    }

    return -1; // No se encontró un ciclo
}

void Graph::DFS(int s) {
    vector<bool> visited(V, false);
    Stack stack;

    stack.push(s);

    while (!stack.isEmpty()) {
        s = stack.pop();

        if (!visited[s]) {
            visited[s] = true;
            cout << s << " ";

            for (auto adjVertex = adj[s].end(); adjVertex != adj[s].begin();) {
                --adjVertex;
                if (!visited[*adjVertex]) {
                    stack.push(*adjVertex);
                }
            }
        }
    }
    cout << endl;
}


class Solution{
public:
    int shortestCycle(vector<vector<int>>& edges, int n){
      int shortestCycleLength = numeric_limits<int>::max();
      Graph G(7);
      for (auto edge : edges) {
          G.addEdge(edge[0], edge[1]);
      }

      for (int i = 0; i < n; ++i) {
          shortestCycleLength = min(shortestCycleLength,     
          G.BFSUtil(i));
      }

      return shortestCycleLength;
      
    }
};

int main() {
  // n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
  vector<vector<int>> edges = {{0,1},{1,2},{2,0},{3,4},{4,5}, 
  {5,6}, {6,3}};
  int n=7;
  cout << Solution().shortestCycle(edges,n);
}
