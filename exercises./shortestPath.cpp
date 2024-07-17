// Problem: Shortest ´Path visiting all nodes
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>

using namespace std;

int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    int finalState = (1 << n) - 1; // Estado en el que todos los nodos han sido visitados
    queue<tuple<int, int, int>> q;
    unordered_set<string> visited;

    // Inicializar la cola con todos los nodos, cada uno como punto de inicio
    for (int i = 0; i < n; ++i) {
        int state = 1 << i;
        q.push({i, state, 0});
        visited.insert(to_string(i) + "-" + to_string(state));
    }

    while (!q.empty()) {
        auto [node, state, dist] = q.front();
        q.pop();

        if (state == finalState) {
            return dist;
        }

        for (int neighbor : graph[node]) {
            int nextState = state | (1 << neighbor);
            string key = to_string(neighbor) + "-" + to_string(nextState);
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                q.push({neighbor, nextState, dist + 1});
            }
        }
    }

    return -1; // Esto nunca debería suceder, ya que el grafo está conectado
}

int main() {
    vector<vector<int>> graph1 = {{1,2,3}, {0}, {0}, {0}};
    cout << "Output 1: " << shortestPathLength(graph1) << endl;

    vector<vector<int>> graph2 = {{1}, {0,2,4}, {1,3,4}, {2}, {1,2}};
    cout << "Output 2: " << shortestPathLength(graph2) << endl;

    return 0;
}
