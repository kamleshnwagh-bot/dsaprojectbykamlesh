# Threaded BST: Inorder Predecessor and Successor

A C++ program to find and display the **inorder predecessor** and **successor** of a specified node in a **threaded Binary Search Tree (BST)**, wherever they exist.

---

## 📌 Problem Statement

Develop a C++ program to find and display the inorder predecessor and successor of a specified node in a threaded binary search tree (BST). The program should build the threaded BST by inserting nodes, replace null child pointers with threads to inorder neighbours, and locate the given node. It should then display its predecessor and successor, wherever they exist, without using recursion or a stack.

---

## 🎯 Objective

- Implement a double-threaded BST in C++.
- Use threads instead of NULL pointers for fast inorder navigation.
- Find the predecessor and successor of any node without recursion or a stack.
- Handle edge cases where a predecessor or successor does not exist.

---

## ✨ Features

- Menu-driven program
- Insert nodes into the threaded BST (duplicates are ignored)
- Stack-free, recursion-free inorder traversal
- Find the inorder predecessor and successor of any node
- Clear messages for "Node not found" and "does not exist"
- Input validation and memory cleanup

---

## 🧠 Concept Used

In a normal BST, many left and right pointers are NULL. In a **double-threaded BST**, every NULL pointer is replaced by a *thread*:

| Field | Meaning |
|-------|---------|
| `lthread = true` | `left` points to the inorder **predecessor** (NULL if none) |
| `rthread = true` | `right` points to the inorder **successor** (NULL if none) |
| `lthread / rthread = false` | `left` / `right` is a normal child link |

---

## ⚙️ Algorithm (Summary)

1. Insert keys into the BST, setting thread links for each new node.
2. Search for the specified key using only real child links.
3. **Successor:** if `rthread = true`, it is `node->right`. Otherwise, go to the right child and keep moving left until `lthread = true`.
4. **Predecessor:** if `lthread = true`, it is `node->left`. Otherwise, go to the left child and keep moving right until `rthread = true`.
5. Display the predecessor and successor, or print "does not exist" if NULL.

---

## ⏱️ Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Insertion | O(h) | O(1) |
| Search | O(h) | O(1) |
| Predecessor / Successor | O(h) worst case | O(1) |
| Inorder traversal | O(n) | O(1) |

*h = height of the tree, n = number of nodes.*

---

## 📁 Project Structure

```
Threaded-BST/
│── threaded_bst.cpp      # Source code
│── Algorithm.pdf         # Step-wise algorithm
│── Flowchart.pdf         # Flowchart of the program
│── Output.png            # Program output screenshots
│── Output_Analysis.md    # Analysis of the output
│── Report.pdf            # Project report
│── README.md             # Project documentation
```

---

## 🚀 How to Compile and Run

**Requirements:** a C++ compiler (g++ recommended)

```bash
g++ threaded_bst.cpp -o threaded_bst
./threaded_bst
```

On Windows:

```bash
g++ threaded_bst.cpp -o threaded_bst.exe
threaded_bst.exe
```

---

## 🧪 Sample Input and Output

**Insert:** 50, 30, 70, 20, 40, 60, 80

```
Inorder: 20 30 40 50 60 70 80
```

| Specified Node | Predecessor | Successor |
|----------------|-------------|-----------|
| 50 | 40 | 60 |
| 20 | does not exist | 30 |
| 80 | 70 | does not exist |
| 99 | Node not found | Node not found |

**Example run (node 50):**

```
Node        : 50
Predecessor : 40
Successor   : 60
```

---

## ⚠️ Edge Cases Handled

- Empty tree
- Node not present in the tree
- Smallest node (no predecessor)
- Largest node (no successor)
- Duplicate key insertion
- Invalid menu or numeric input

---

## 💡 Applications

- Memory-efficient inorder traversal without a stack
- Database indexing and ordered data access
- Range queries and nearest-neighbour lookups
- Symbol tables and compilers

---

## 🔮 Future Scope

- Add node deletion with thread updates
- Add a visual display of the tree structure
- Convert to a template class for any data type

---

## 👤 Author

**Name:** Your Name
**Roll No:** Your Roll Number
**Course:** Data Structures and Algorithms
**Institute:** Your College / University

---

⭐ If you found this project helpful, consider giving it a star!
