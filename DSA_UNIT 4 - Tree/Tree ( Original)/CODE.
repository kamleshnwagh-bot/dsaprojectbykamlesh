
/*
 * Threaded BST: Inorder Predecessor and Successor
 * ------------------------------------------------
 * A double-threaded BST: every NULL left/right child pointer is replaced by
 * a "thread" pointing to the inorder predecessor / successor.
 *   lthread == true  -> left  points to inorder predecessor (or NULL if none)
 *   rthread == true  -> right points to inorder successor   (or NULL if none)
 */

#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) : data(val), left(nullptr), right(nullptr),
                    lthread(true), rthread(true) {}
};

// Insert a key, maintaining threads. Returns the (possibly new) root.
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
    if (!parent) return node;  // first node: both threads NULL

    if (key < parent->data) {
        node->left = parent->left;   // inherit predecessor
        node->right = parent;        // successor is parent
        parent->left = node;
        parent->lthread = false;
    } else {
        node->right = parent->right; // inherit successor
        node->left = parent;         // predecessor is parent
        parent->right = node;
        parent->rthread = false;
    }
    return root;
}

// Find the node holding 'key' (nullptr if absent).
Node* search(Node* root, int key) {
    Node* cur = root;
    while (cur) {
        if (key == cur->data) return cur;
        if (key < cur->data) cur = cur->lthread ? nullptr : cur->left;
        else                 cur = cur->rthread ? nullptr : cur->right;
    }
    return nullptr;
}

// Inorder successor using threads.
Node* inorderSuccessor(Node* node) {
    if (node->rthread) return node->right;   // thread (may be NULL)
    node = node->right;                      // leftmost of right subtree
    while (!node->lthread) node = node->left;
    return node;
}

// Inorder predecessor using threads.
Node* inorderPredecessor(Node* node) {
    if (node->lthread) return node->left;    // thread (may be NULL)
    node = node->left;                       // rightmost of left subtree
    while (!node->rthread) node = node->right;
    return node;
}

// Stack-free, recursion-free inorder traversal.
void inorder(Node* root) {
    if (!root) { cout << "Tree is empty.\n"; return; }
    Node* cur = root;
    while (!cur->lthread) cur = cur->left;   // leftmost node
    while (cur) {
        cout << cur->data << " ";
        cur = inorderSuccessor(cur);
    }
    cout << "\n";
}

void freeTree(Node* root) {
    if (!root) return;
    if (!root->lthread) freeTree(root->left);
    if (!root->rthread) freeTree(root->right);
    delete root;
}

void findPredSucc(Node* root, int key) {
    Node* node = search(root, key);
    if (!node) {
        cout << "Node " << key << " not found in the tree.\n";
        return;
    }
    Node* pred = inorderPredecessor(node);
    Node* succ = inorderSuccessor(node);

    cout << "Node        : " << node->data << "\n";
    if (pred) cout << "Predecessor : " << pred->data << "\n";
    else      cout << "Predecessor : does not exist\n";
    if (succ) cout << "Successor   : " << succ->data << "\n";
    else      cout << "Successor   : does not exist\n";
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
             << "4. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1:
                root = insert(root, readInt("Enter value to insert: "));
                break;
            case 2:
                cout << "Inorder: ";
                inorder(root);
                break;
            case 3:
                if (!root) cout << "Tree is empty.\n";
                else findPredSucc(root, readInt("Enter node value: "));
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    freeTree(root);
    return 0;
}
