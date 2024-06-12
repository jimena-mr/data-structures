// Class B Tree
#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);

    void traverse();

    BTreeNode *search(int k);

    void insert(int k);

    friend class BTree;
};

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (leaf == false)
        C[i]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (keys[i] == k)
        return this;
    if (leaf == true)
        return nullptr;
    return C[i]->search(k);
}

void BTreeNode::insert(int k) {
    if (leaf == true) {
        int i = n-1;
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    } else {
        int i = n-1;
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i+1]->n == 2*t-1) {
            BTreeNode *newNode = new BTreeNode(t, leaf);
            newNode->keys[0] = keys[t-1];
            newNode->n = t-1;
            for (int j = 0; j < t-1; j++)
                newNode->keys[j] = C[i+1]->keys[j+t];
            if (C[i+1]->leaf == false) {
                for (int j = 0; j < t; j++)
                    newNode->C[j] = C[i+1]->C[j+t];
            }
            C[i+1]->n = t-1;
            for (int j = n; j >= i+1; j--)
                C[j+1] = C[j];
            C[i+1] = newNode;
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insert(k);
    }
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2*t-1) {
            BTreeNode *newNode = new BTreeNode(t, false);
            newNode->C[0] = root;
            newNode->keys[0] = root->keys[t-1];
            newNode->n = 1;
            root->n = t-1;
            newNode->insert(k);
            root = newNode;
        } else {
            root->insert(k);
        }
    }
}

int main() {
    BTree btree(3); // Grado del B-Tree

    btree.insert(10);
    btree.insert(20);
    btree.insert(5);
    btree.insert(6);
    btree.insert(12);
    btree.insert(30);
    btree.insert(7);
    btree.insert(17);

    cout << "Recorrido del árbol construido:\n";
    btree.traverse();
    cout << endl;

    // Buscar elementos
    int keyToSearch = 30;
    cout << "El elemento " << keyToSearch << " " << (btree.search(keyToSearch) ? "está presente" : "no está presente") << " en el árbol." << endl;

    keyToSearch = 15;
    cout << "El elemento " << keyToSearch << " " << (btree.search(keyToSearch) ? "está presente" : "no está presente") << " en el árbol." << endl;

    return 0;
}
