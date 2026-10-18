# 🏥 Hospital Patient Management System Using Circular Doubly Linked List, Array and Queue

## 📌 Project Overview

The Hospital Patient Management System is a C++ mini-project that manages patient records using three data structures working together. Patient details are stored in a Circular Doubly Linked List, hospital beds are managed using an Array, and discharged patients are held in a Queue so that the oldest discharged patient can be re-admitted.

The project is written using structures only (no classes) and has a menu-driven interface.

## 🎯 Objectives

- To manage admitted patient records efficiently.
- To implement a Circular Doubly Linked List, an Array and a Queue in C++.
- To perform admission, discharge, searching and display operations.
- To allocate and free hospital beds automatically.
- To understand dynamic memory allocation and pointer manipulation.

## ✨ Features

- Admit a new patient and allot a free bed automatically.
- Discharge a patient and free the bed.
- Search a patient by ID.
- Display all patient records in forward and backward order.
- Show the status of all hospital beds.
- Re-admit the oldest discharged patient (undo discharge).
- View discharge history (oldest discharge first).
- Duplicate ID checking.
- Menu-driven user interface.

## 🛠️ Technologies Used

- Programming Language: C++
- Data Structures: Circular Doubly Linked List, Queue (circular array based), Array
- Concepts: Structures, Pointers, Dynamic Memory Allocation, Functions and Loops
- Platform: Visual Studio Code / Code::Blocks / any compatible C++ compiler

## ⚙️ How It Works

1. The user selects an operation from the menu.
2. While admitting, the system finds the first free bed in the bed array.
3. Patient details are entered and stored as a new node at the end of the circular doubly linked list.
4. While discharging, the patient record is added to the queue, the bed is freed and the node is removed from the list.
5. Undo removes the oldest record from the front of the queue and inserts the patient back into the list.

## 🧩 Data Structures Used

| Data Structure | Used For |
|---|---|
| Circular Doubly Linked List | Stores admitted patient records (forward and backward traversal) |
| Array (10 beds) | Bed allocation and availability |
| Queue (5 records) | Discharge history and re-admission of the oldest discharged patient |

### Node Structure

Each node of the circular linked list contains:

- Patient ID
- Patient Name
- Age
- Disease
- Allotted Bed Number
- Previous pointer
- Next pointer

The last node's `next` pointer points to the head, and the head's `prev` pointer points to the last node.

## ▶️ How to Run the Project

1. Clone or download this repository.
2. Open the project folder in your preferred C++ IDE.
3. Compile the source code using a C++ compiler.

```bash
g++ hospital_circular.cpp -o hospital
```

4. Run the program.

Windows:

```bash
hospital.exe
```

Linux/macOS:

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
| 7 | Undo discharge (re-admit oldest discharged) |
| 8 | Show discharge history |
| 0 | Exit |

## 📚 Data Structure Operations

| Operation | Description | Time Complexity |
|---|---|---|
| Admit | Checks the ID, adds a patient at the end of the list and occupies a bed | O(n) |
| Discharge | Enqueues record, frees bed, removes node | O(n) |
| Searching | Finds a patient by ID | O(n) |
| Forward Traversal | Displays records from head to tail | O(n) |
| Backward Traversal | Displays records from tail to head | O(n) |
| Bed Status | Scans the bed array | O(1) |
| Undo Discharge | Dequeues the oldest record and re-admits the patient | O(n) |
| Discharge History | Prints queue from front to rear | O(1) |

## ✅ Advantages

- Supports traversal in both directions.
- Allows dynamic addition and removal of records.
- Insertion at the end is fast because the tail is reached directly using `head->prev`.
- Deletion is efficient once the node is found, since both neighbours are linked.
- The circular structure allows traversal to continue from the tail back to the head.
- The queue keeps discharge history in the order in which patients were discharged.
- Demonstrates practical use of three data structures in a hospital scenario.

## ⚠️ Limitations

- Records are lost when the program terminates, as file storage is not implemented.
- The hospital has a fixed number of beds (10) and the discharge history is limited to 5 records. When the queue is full, the oldest record is removed.
- Undo re-admits the oldest discharged patient, not the most recent one, because a queue is first-in, first-out.
- Searching for a patient requires linear traversal.
- The project is intended for educational purposes and is not a production-ready hospital system.

## 🔮 Future Enhancements

- Add file handling or database integration for permanent storage.
- Add an option to update patient details.
- Search patients by name.
- Implement doctor and department management.
- Introduce appointment scheduling and billing.
- Add login authentication and role-based access.

## 🎓 Learning Outcomes

- Understand the working of a Circular Doubly Linked List, Queue and Array.
- Develop practical C++ programming skills.
- Learn dynamic memory management and pointer operations.
- Apply data structures to a real-world inspired problem.

## 👨‍💻 Author

Student Mini-Project — Data Structures and Algorithms (DSA)

## 📄 License

This project is intended for educational and academic purposes.