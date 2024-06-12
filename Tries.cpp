// Class Trie
#include <vector>
#include <string>
using namespace std;

struct MyTrie {
    vector<vector<int>> tr;
    vector<bool> is_word;
    int root, id;

    MyTrie() {
        init();
    }

    void init() {
        root = 0;
        id = 1;
        tr.push_back(vector<int>(26, -1));
        is_word.push_back(false);
    }

    int newNode() {
        tr.push_back(vector<int>(26, -1));
        is_word.push_back(false);
        return id++;
    }

    void add(const string& s) {
        int u = root;
        for(char ch : s) {
            int c = ch - 'a';
            if(tr[u][c] == -1) {
                tr[u][c] = newNode();
            }
            u = tr[u][c];
        }
        is_word[u] = true;
    }

    int find(const string& s) const {
        int u = root;
        for(char ch : s) {
            int c = ch - 'a';
            if(u == -1) return -1;
            u = tr[u][c];
        }
        return u;
    }
};

class Trie {
public:
    MyTrie tr;

    Trie() = default;

    void insert(const string& word) {
        tr.add(word);
    }

    bool search(const string& word) const {
        int node = tr.find(word);
        return node != -1 && tr.is_word[node];
    }

    bool startsWith(const string& prefix) const {
        int node = tr.find(prefix);
        return node != -1;
    }
};


int main() {
    Trie trie;
    
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("band");
    
    cout << (trie.search("apple") ? "Found 'apple'" : "Did not find 'apple'") << endl;
    cout << (trie.search("app") ? "Found 'app'" : "Did not find 'app'") << endl;
    cout << (trie.search("ban") ? "Found 'ban'" : "Did not find 'ban'") << endl;
    cout << (trie.search("band") ? "Found 'band'" : "Did not find 'band'") << endl;
    
    cout << (trie.startsWith("app") ? "'app' is a prefix" : "'app' is not a prefix") << endl;
    cout << (trie.startsWith("ban") ? "'ban' is a prefix" : "'ban' is not a prefix") << endl;
    cout << (trie.startsWith("bat") ? "'bat' is a prefix" : "'bat' is not a prefix") << endl;
    
    return 0;
}
