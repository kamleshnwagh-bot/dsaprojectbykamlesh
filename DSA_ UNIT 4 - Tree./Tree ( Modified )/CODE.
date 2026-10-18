/*
 * Threaded BST: Inorder Predecessor and Successor (Modified Version)
 * -------------------------------------------------------------------
 * Double-threaded BST: every NULL child pointer is replaced by a thread.
 *   lthread == true  -> left  points to inorder predecessor (NULL if none)
 *   rthread == true  -> right points to inorder successor   (NULL if none)
 *
 * Modifications:
 *   1. Minimum and maximum nodes (no predecessor / successor) are handled
 *      and reported clearly.
 *   2. Predecessor and successor are displayed for EVERY node.
 *   3. Results are verified against the inorder traversal sequence.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) : data(val), left(nullptr), right(nullptr),
                    lthread(true), rthread(true) {}
};

// ---------- Insertion ----------
Node* insert(Node* root, int key) {
    Node *parent = nullptr, *cur = root;

    while (cur) {
        if (key == cur->data) {
            cout << "Duplicate key " << key << " ignored.\n";
            return root;
        }
        parent = cur;
        if (key < cur->data) {
            if (cur->lthread) break;
            cur = cur->left;
        } else {
            if (cur->rthread) break;
            cur = cur->right;
        }
    }

    Node* node = new Node(key);
    if (!parent) return node;               // first node

    if (key < parent->data) {
        node->left = parent->left;          // inherit predecessor
        node->right = parent;               // successor is parent
        parent->left = node;
        parent->lthread = false;
    } else {
        node->right = parent->right;        // inherit successor
        node->left = parent;                // predecessor is parent
        parent->right = node;
        parent->rthread = false;
    }
    return root;
}

// ---------- Search ----------
Node* search(Node* root, int key) {
    Node* cur = root;
    while (cur) {
        if (key == cur->data) return cur;
        if (key < cur->data) cur = cur->lthread ? nullptr : cur->left;
        else                 cur = cur->rthread ? nullptr : cur->right;
    }
    return nullptr;
}

// ---------- Successor / Predecessor (using threads) ----------
Node* inorderSuccessor(Node* node) {
    if (node->rthread) return node->right;  // thread (NULL for maximum node)
    node = node->right;
    while (!node->lthread) node = node->left;
    return node;
}

Node* inorderPredecessor(Node* node) {
    if (node->lthread) return node->left;   // thread (NULL for minimum node)
    node = node->left;
    while (!node->rthread) node = node->right;
    return node;
}

Node* minNode(Node* root) {
    while (root && !root->lthread) root = root->left;
    return root;
}

Node* maxNode(Node* root) {
    while (root && !root->rthread) root = root->right;
    return root;
}

// ---------- Inorder traversal (no recursion, no stack) ----------
vector<int> inorderSequence(Node* root) {
    vector<int> seq;
    for (Node* cur = minNode(root); cur; cur = inorderSuccessor(cur))
        seq.push_back(cur->data);
    return seq;
}

void displayInorder(Node* root) {
    if (!root) { cout << "Tree is empty.\n"; return; }
    vector<int> seq = inorderSequence(root);
    cout << "Inorder: ";
    for (int v : seq) cout << v << " ";
    cout << "\n";
}

void freeTree(Node* root) {
    if (!root) return;
    if (!root->lthread) freeTree(root->left);
    if (!root->rthread) freeTree(root->right);
    delete root;
}

// ---------- Display helpers ----------
string predText(Node* root, Node* node) {
    Node* p = inorderPredecessor(node);
    if (p) return to_string(p->data);
    return (node == minNode(root)) ? "None (minimum node)" : "None";
}

string succText(Node* root, Node* node) {
    Node* s = inorderSuccessor(node);
    if (s) return to_string(s->data);
    return (node == maxNode(root)) ? "None (maximum node)" : "None";
}

// Modification 1: single node, min/max handled
void findPredSucc(Node* root, int key) {
    Node* node = search(root, key);
    if (!node) {
        cout << "Node " << key << " not found in the tree.\n";
        return;
    }
    cout << "Node        : " << node->data << "\n"
         << "Predecessor : " << predText(root, node) << "\n"
         << "Successor   : " << succText(root, node) << "\n";
}

// Modification 2: every node
void displayAll(Node* root) {
    if (!root) { cout << "Tree is empty.\n"; return; }
    cout << "\n" << left << setw(8) << "Node" << setw(24) << "Predecessor"
         << setw(24) << "Successor" << "\n"
         << string(56, '-') << "\n";
    for (Node* cur = minNode(root); cur; cur = inorderSuccessor(cur)) {
        cout << left << setw(8) << cur->data
             << setw(24) << predText(root, cur)
             << setw(24) << succText(root, cur) << "\n";
    }
}

// Modification 3: verify against inorder sequence
void verify(Node* root) {
    if (!root) { cout << "Tree is empty.\n"; return; }
    vector<int> seq = inorderSequence(root);
    int n = seq.size(), passed = 0;

    cout << "\nInorder sequence: ";
    for (int v : seq) cout << v << " ";
    cout << "\n\n" << left << setw(8) << "Node" << setw(14) << "Pred(thread)"
         << setw(14) << "Pred(seq)" << setw(14) << "Succ(thread)"
         << setw(14) << "Succ(seq)" << "Result\n"
         << string(70, '-') << "\n";

    for (int i = 0; i < n; i++) {
        Node* node = search(root, seq[i]);
        Node* p = inorderPredecessor(node);
        Node* s = inorderSuccessor(node);

        bool predOk = (i == 0) ? (p == nullptr) : (p && p->data == seq[i - 1]);
        bool succOk = (i == n - 1) ? (s == nullptr) : (s && s->data == seq[i + 1]);
        bool ok = predOk && succOk;
        if (ok) passed++;

        string ps = p ? to_string(p->data) : "None";
        string ss = s ? to_string(s->data) : "None";
        string pe = (i == 0) ? "None" : to_string(seq[i - 1]);
        string se = (i == n - 1) ? "None" : to_string(seq[i + 1]);

        cout << left << setw(8) << seq[i] << setw(14) << ps << setw(14) << pe
             << setw(14) << ss << setw(14) << se << (ok ? "PASS" : "FAIL") << "\n";
    }
    cout << "\nVerification: " << passed << "/" << n << " nodes matched. "
         << (passed == n ? "ALL RESULTS CORRECT.\n" : "MISMATCH FOUND.\n");
}

int readInt(const char* prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    return x;
}

int main() {
    Node* root = nullptr;
    int choice;

    do {
        cout << "\n===== Threaded BST Menu =====\n"
             << "1. Insert a node\n"
             << "2. Display inorder traversal\n"
             << "3. Find predecessor & successor of a node\n"
             << "4. Display predecessor & successor of every node\n"
             << "5. Verify results against inorder sequence\n"
             << "6. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: root = insert(root, readInt("Enter value to insert: ")); break;
            case 2: displayInorder(root); break;
            case 3:
                if (!root) cout << "Tree is empty.\n";
                else findPredSucc(root, readInt("Enter node value: "));
                break;
            case 4: displayAll(root); break;
            case 5: verify(root); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    freeTree(root);
    return 0;
}

