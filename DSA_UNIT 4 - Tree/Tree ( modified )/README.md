# Threaded BST: Inorder Predecessor and Successor (Modified)

A C++ program that builds a **threaded Binary Search Tree (BST)** and finds the **inorder predecessor and successor** of a specified node and of every node. It handles the minimum and maximum nodes and verifies all results against the inorder traversal sequence.

---

## 📌 Problem Statement

Develop a C++ program to build a threaded binary search tree (BST) and display the inorder predecessor and successor of a specified node as well as every node. The program should handle the minimum and maximum nodes that lack a predecessor or successor, and verify all results against the inorder traversal sequence.

---

## 🎯 Objective

- Implement a double-threaded BST in C++.
- Find the predecessor and successor of any node using threads, without recursion or a stack.
- Handle the minimum and maximum nodes that have no predecessor or successor.
- Verify all results against the inorder traversal sequence.

---

## 🛠️ Modifications

| No. | Modification | How it is done |
|-----|--------------|----------------|
| 1 | Handle minimum and maximum nodes | The minimum node shows `None (minimum node)` as its predecessor. The maximum node shows `None (maximum node)` as its successor. |
| 2 | Display predecessor and successor for every node | Menu option 4 prints a table for all nodes. |
| 3 | Verify results against the inorder sequence | Menu option 5 compares each node's thread-based result with its neighbours in the sequence and marks it PASS or FAIL. |

---

## ✨ Features

- Menu-driven program
- Insert nodes (duplicates are ignored)
- Stack-free, recursion-free inorder traversal
- Predecessor and successor of a specified node
- Predecessor and successor table for every node
- Automatic verification with PASS / FAIL result
- Input validation and memory cleanup

---

## 🧠 Concept Used

In a **double-threaded BST**, every NULL child pointer is replaced by a *thread*:

| Field | Meaning |
|-------|---------|
| `lthread = true` | `left` points to the inorder **predecessor** (NULL if none) |
| `rthread = true` | `right` points to the inorder **successor** (NULL if none) |
| `lthread / rthread = false` | `left` / `right` is a normal child link |

---

## ⚙️ Algorithm

1. Start and set `root = NULL`.
2. Create a node with `data`, `left`, `right`, `lthread` and `rthread`.
3. Read a key. If the tree is empty, make it the root.
4. Otherwise, move left or right until the next link is a thread. Ignore duplicates.
5. Insert the new node and set its threads and the parent's thread flag.
6. Successor: use the right thread if `rthread = true`. Otherwise, take the leftmost node of the right subtree.
7. Predecessor: use the left thread if `lthread = true`. Otherwise, take the rightmost node of the left subtree.
8. Find the minimum node by going left until `lthread = true`, and the maximum node by going right until `rthread = true`.
9. For a specified node, search for it. If it is not found, display "Node not found".
10. If found, display its predecessor and successor. Show "None (minimum node)" or "None (maximum node)" if NULL.
11. For every node, start at the minimum node and display each node's predecessor and successor until NULL.
12. Store the inorder sequence by following successor links from the minimum node.
13. Compare each node's thread-based predecessor and successor with its neighbours in the sequence. Mark each PASS or FAIL.
14. Repeat the menu until exit, then free memory and stop.

---

## ⏱️ Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Insertion | O(h) | O(1) |
| Search | O(h) | O(1) |
| Predecessor / Successor of one node | O(h) | O(1) |
| Display for every node | O(n) | O(1) |
| Verification | O(n·h) | O(n) |

*n = number of nodes, h = height of the tree. Verification stores the inorder sequence and searches for each node.*

---

## 📁 Project Structure

```
Threaded-BST-Modified/
│── threaded_bst_modified.cpp   # Source code
│── Algorithm.pdf               # Step-wise algorithm
│── Flowchart_.pdf              # Flowchart of the program
│── Output_.pdf                 # Program output screenshots
│── Output_analysis.pdf         # Analysis of the output
│── Report_.pdf                 # Project report
│── README.md                   # Project documentation
```

---

## 🚀 How to Compile and Run

**Requirements:** a C++ compiler (g++ recommended)

```bash
g++ threaded_bst_modified.cpp -o threaded_bst_modified
./threaded_bst_modified
```

On Windows:

```bash
g++ threaded_bst_modified.cpp -o threaded_bst_modified.exe
threaded_bst_modified.exe
```

**Quick test:** after starting the program, enter this and press Enter:

```
1 50 1 30 1 70 1 20 1 40 1 60 1 80 4 5 6
```

---

## 🧪 Sample Output

**Tree built from:** 50, 30, 70, 20, 40, 60, 80

```
Inorder: 20 30 40 50 60 70 80
```

**Option 4: predecessor and successor of every node**

```
Node    Predecessor             Successor
--------------------------------------------------------
20      None (minimum node)     30
30      20                      40
40      30                      50
50      40                      60
60      50                      70
70      60                      80
80      70                      None (maximum node)
```

**Option 5: verification against the inorder sequence**

```
Node    Pred(thread)  Pred(seq)     Succ(thread)  Succ(seq)     Result
----------------------------------------------------------------------
20      None          None          30            30            PASS
30      20            20            40            40            PASS
40      30            30            50            50            PASS
50      40            40            60            60            PASS
60      50            50            70            70            PASS
70      60            60            80            80            PASS
80      70            70            None          None          PASS

Verification: 7/7 nodes matched. ALL RESULTS CORRECT.
```

---

## ⚠️ Edge Cases Handled

- Empty tree
- Tree with a single node (both predecessor and successor are None)
- Minimum node (no predecessor)
- Maximum node (no successor)
- Node not present in the tree
- Duplicate key insertion
- Invalid menu or numeric input

---

## 💡 Applications

- Memory-efficient inorder traversal without a stack
- Ordered data access and range queries
- Symbol tables and compilers

---

## 👤 Author

**Name:** Your Name
**Roll No:** Your Roll Number
**Course:** Data Structures and Algorithms
**Institute:** Your College / University
