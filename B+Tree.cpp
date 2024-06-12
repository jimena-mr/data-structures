// Class B tree
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BPTreeNode {
public:
    vector<int> keys;
    vector<BPTreeNode*> children;
    BPTreeNode* next;
    bool isLeaf;

    BPTreeNode(bool leaf) {
        isLeaf = leaf;
        next = nullptr;
    }
};

class BPTree {
public:
    BPTreeNode* root;
    int t;

    BPTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void insert(int k);
    bool search(int k);
    void traverse();

private:
    void insertInternal(int k, BPTreeNode* node, BPTreeNode* parent);
    void traverse(BPTreeNode* node);
    BPTreeNode* findLeaf(int k);
};

void BPTree::traverse() {
    if (root != nullptr) traverse(root);
}

void BPTree::traverse(BPTreeNode* node) {
    if (node->isLeaf) {
        for (int key : node->keys)
            cout << key << " ";
        if (node->next != nullptr)
            traverse(node->next);
    } else {
        for (size_t i = 0; i < node->children.size(); i++)
            traverse(node->children[i]);
    }
}

BPTreeNode* BPTree::findLeaf(int k) {
    BPTreeNode* current = root;
    while (!current->isLeaf) {
        size_t i;
        for (i = 0; i < current->keys.size(); i++) {
            if (k < current->keys[i])
                break;
        }
        current = current->children[i];
    }
    return current;
}

void BPTree::insert(int k) {
    if (root == nullptr) {
        root = new BPTreeNode(true);
        root->keys.push_back(k);
    } else {
        BPTreeNode* leaf = findLeaf(k);
        if (leaf->keys.size() < t - 1) {
            leaf->keys.push_back(k);
            sort(leaf->keys.begin(), leaf->keys.end());
        } else {
            BPTreeNode* newLeaf = new BPTreeNode(true);
            vector<int> tempKeys = leaf->keys;
            tempKeys.push_back(k);
            sort(tempKeys.begin(), tempKeys.end());

            leaf->keys.resize((t + 1) / 2);
            for (int i = 0; i < (t + 1) / 2; i++)
                leaf->keys[i] = tempKeys[i];

            for (int i = (t + 1) / 2; i < t; i++)
                newLeaf->keys.push_back(tempKeys[i]);

            newLeaf->next = leaf->next;
            leaf->next = newLeaf;

            if (leaf == root) {
                BPTreeNode* newRoot = new BPTreeNode(false);
                newRoot->keys.push_back(newLeaf->keys[0]);
                newRoot->children.push_back(leaf);
                newRoot->children.push_back(newLeaf);
                root = newRoot;
            } else {
                insertInternal(newLeaf->keys[0], leaf, nullptr);
            }
        }
    }
}

void BPTree::insertInternal(int k, BPTreeNode* node, BPTreeNode* parent) {
    if (parent == nullptr) {
        parent = findLeaf(k);
    }

    if (parent->keys.size() < t - 1) {
        parent->keys.push_back(k);
        sort(parent->keys.begin(), parent->keys.end());
        for (size_t i = 0; i < parent->keys.size(); i++) {
            if (parent->keys[i] == k) {
                parent->children[i + 1] = node->next;
                break;
            }
        }
    } else {
        BPTreeNode* newInternal = new BPTreeNode(false);
        vector<int> tempKeys = parent->keys;
        tempKeys.push_back(k);
        sort(tempKeys.begin(), tempKeys.end());

        parent->keys.resize((t + 1) / 2);
        for (int i = 0; i < (t + 1) / 2; i++)
            parent->keys[i] = tempKeys[i];

        for (int i = (t + 1) / 2 + 1; i < t; i++)
            newInternal->keys.push_back(tempKeys[i]);

        newInternal->children.resize((t + 1) / 2 + 1);
        for (int i = (t + 1) / 2, j = 0; i < t + 1; i++, j++)
            newInternal->children[j] = parent->children[i];

        for (int i = 0; i < newInternal->children.size(); i++)
            newInternal->children[i]->next = nullptr;

        if (parent == root) {
            BPTreeNode* newRoot = new BPTreeNode(false);
            newRoot->keys.push_back(newInternal->keys[0]);
            newRoot->children.push_back(parent);
            newRoot->children.push_back(newInternal);
            root = newRoot;
        } else {
            insertInternal(newInternal->keys[0], newInternal, nullptr);
        }
    }
}

bool BPTree::search(int k) {
    BPTreeNode* leaf = findLeaf(k);
    for (int key : leaf->keys) {
        if (key == k) return true;
    }
    return false;
}

int main() {
    BPTree bptree(3); // Grado del B+ Tree

    bptree.insert(10);
    bptree.insert(20);
    bptree.insert(5);
    bptree.insert(6);
    bptree.insert(12);
    bptree.insert(30);
    bptree.insert(7);
    bptree.insert(17);

    cout << "Recorrido del árbol construido:\n";
    bptree.traverse();
    cout << endl;

    // Buscar elementos
    int keyToSearch = 30;
    cout << "El elemento " << keyToSearch << " " << (bptree.search(keyToSearch) ? "está presente" : "no está presente") << " en el árbol." << endl;

    keyToSearch = 15;
    cout << "El elemento " << keyToSearch << " " << (bptree.search(keyToSearch) ? "está presente" : "no está presente") << " en el árbol." << endl;
}
