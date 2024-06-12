// Class Trie
#include <iostream>
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

    bool remove(const string& s) {
        int u = find(s);
        if (u == -1 || !is_word[u]) return false; // Word doesn't exist in trie
        is_word[u] = false;
        return true;
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

    bool remove(const string& word) {
        return tr.remove(word);
    }

    vector<string> stringMatching(const string& pattern) const {
        vector<string> matched_words;
        for (size_t i = 0; i < pattern.length(); ++i) {
            string prefix = pattern.substr(0, i + 1);
            if (startsWith(prefix)) {
                matched_words.push_back(prefix);
            }
        }
        return matched_words;
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
    
    cout << "Words matching 'app': ";
    vector<string> matched_words = trie.stringMatching("app");
    for (const string& word : matched_words) {
        cout << word << " ";
    }
    cout << endl;

    cout << "Words matching 'ban': ";
    matched_words = trie.stringMatching("ban");
    for (const string& word : matched_words) {
        cout << word << " ";
    }
    cout << endl;

    cout << "Words matching 'b': ";
    matched_words = trie.stringMatching("b");
    for (const string& word : matched_words) {
        cout << word << " ";
    }
    cout << endl;

    trie.remove("apple");
    cout << (trie.search("apple") ? "Found 'apple'" : "Did not find 'apple'") << endl;
}
