# 🏥 Hospital Patient Management System Using Doubly Linked List, Stack and Array

## 📌 Project Overview

The Hospital Patient Management System is a C++ mini-project that manages patient records using three data structures working together. Patient details are stored in a **Doubly Linked List**, hospital beds are managed using an **Array**, and discharged patients are saved in a **Stack** so that the last discharge can be undone.

The project is written using structures only (no classes) and has a menu-driven interface.

## 🎯 Objectives

- To manage admitted patient records efficiently.
- To implement a Doubly Linked List, a Stack and an Array in C++.
- To perform admission, discharge, searching and display operations.
- To allocate and free hospital beds automatically.
- To understand dynamic memory allocation and pointer manipulation.

## ✨ Features

- Admit a new patient and allot a free bed automatically.
- Discharge a patient and free the bed.
- Search a patient by ID or by name.
- Display all patient records in forward and backward order.
- Show the status of all hospital beds.
- Undo the last discharge.
- View discharge history (latest discharge first).
- Input validation and duplicate ID checking.
- Menu-driven user interface.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Data Structures:** Doubly Linked List, Stack (array based), Array
- **Concepts:** Structures, Pointers, Dynamic Memory Allocation, Functions and Loops
- **Platform:** Visual Studio Code / Code::Blocks / any compatible C++ compiler

## ⚙️ How It Works

1. The user selects an operation from the menu.
2. While admitting, the system finds the first free bed in the bed array.
3. Patient details are entered and stored as a new node at the end of the doubly linked list.
4. While discharging, the patient record is pushed onto the stack, the bed is freed and the node is removed from the list.
5. Undo pops the last record from the stack and inserts the patient back into the list.

## 🧩 Data Structures Used

| Data Structure | Used For |
|---|---|
| Doubly Linked List | Stores admitted patient records (forward and backward traversal) |
| Array (10 beds) | Bed allocation and availability |
| Stack (50 records) | Discharge history and undo last discharge |

### Node Structure

Each node of the linked list contains:

- Patient ID
- Patient Name
- Age
- Disease
- Allotted Bed Number
- Previous pointer
- Next pointer

## ▶️ How to Run the Project

1. Clone or download this repository.
2. Open the project folder in your preferred C++ IDE.
3. Compile the source code using a C++ compiler.

```bash
g++ hospital_management.cpp -o hospital
```

4. Run the program.

**Windows:**

```bash
hospital.exe
```

**Linux/macOS:**

```bash
./hospital
```

## 📋 Menu Options

| Choice | Operation |
|---|---|
| 1 | Admit new patient |
| 2 | Discharge patient |
| 3 | Search patient |
| 4 | Display all patients (forward) |
| 5 | Display all patients (backward) |
| 6 | Show bed status |
| 7 | Undo last discharge |
| 8 | Show discharge history |
| 0 | Exit |

## 📚 Data Structure Operations

| Operation | Description | Time Complexity |
|---|---|---|
| Admit | Adds a patient at the end of the list and occupies a bed | O(n) |
| Discharge | Pushes record to stack, frees bed, removes node | O(n) |
| Searching | Finds a patient by ID or name | O(n) |
| Forward Traversal | Displays records from first to last | O(n) |
| Backward Traversal | Displays records from last to first | O(n) |
| Bed Status | Scans the bed array | O(1) |
| Undo Discharge | Pops stack and re-admits the patient | O(n) |
| Discharge History | Prints stack from top to bottom | O(1) |

## ✅ Advantages

- Supports traversal in both directions.
- Allows dynamic addition and removal of records.
- Insertion at the end is fast because a tail pointer is maintained.
- Deletion is efficient once the node is found, since both neighbours are linked.
- Undo feature is simple and quick using a stack.
- Demonstrates practical use of three data structures in a hospital scenario.

## ⚠️ Limitations

- Records are lost when the program terminates, as file storage is not implemented.
- The hospital has a fixed number of beds (10) and discharge history is limited to 50 records.
- Searching for a patient requires linear traversal.
- The project is intended for educational purposes and is not a production-ready hospital system.

## 🔮 Future Enhancements

- Add file handling or database integration for permanent storage.
- Add an option to update patient details.
- Implement doctor and department management.
- Introduce appointment scheduling and billing.
- Add login authentication and role-based access.

## 🎓 Learning Outcomes

- Understand the working of a Doubly Linked List, Stack and Array.
- Develop practical C++ programming skills.
- Learn dynamic memory management and pointer operations.
- Apply data structures to a real-world inspired problem.

## 👨‍💻 Author

Student Mini-Project — Data Structures and Algorithms (DSA)

## 📄 License

This project is intended for educational and academic purposes.
