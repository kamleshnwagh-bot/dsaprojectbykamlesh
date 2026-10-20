// Hospital Patient Management System
// Data structures: Circular (doubly) linked list + Array + Queue
//   - Circular doubly linked list : patient records (admit, discharge, search, forward/backward display)
//   - Array                       : hospital beds (bed allocation)
//   - Queue (circular array)      : discharged patients (FIFO discharge history, re-admit oldest)

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_BEDS = 10;
const int QSIZE = 5;   // queue capacity (small so overflow handling is easy to demo)

struct Patient {
    int id;
    char name[30];
    int age;
    char disease[30];
    int bed;           // allotted bed number (1..MAX_BEDS)
};

struct Node {
    Patient data;
    Node *next;
    Node *prev;
};

// ---------- Globals ----------
Node *head = NULL;            // circular list: tail = head->prev, tail->next = head
int beds[MAX_BEDS];           // 0 = free, 1 = occupied
int patientCount = 0;

Patient dq[QSIZE];            // circular queue of discharged patients
int qFront = 0, qRear = -1, qCount = 0;

// ---------- Queue operations ----------
bool queueEmpty() { return qCount == 0; }
bool queueFull()  { return qCount == QSIZE; }

void enqueue(Patient p) {
    qRear = (qRear + 1) % QSIZE;
    dq[qRear] = p;
    qCount++;
}

Patient dequeue() {
    Patient p = dq[qFront];
    qFront = (qFront + 1) % QSIZE;
    qCount--;
    return p;
}

// ---------- Bed array operations ----------
int findFreeBed() {
    for (int i = 0; i < MAX_BEDS; i++)
        if (beds[i] == 0) return i;
    return -1;
}

// ---------- Circular linked list operations ----------
Node *findPatient(int id) {
    if (head == NULL) return NULL;
    Node *cur = head;
    do {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    } while (cur != head);
    return NULL;
}

void insertEnd(Patient p) {
    Node *n = new Node;
    n->data = p;
    if (head == NULL) {
        n->next = n;
        n->prev = n;
        head = n;
    } else {
        Node *tail = head->prev;
        tail->next = n;
        n->prev = tail;
        n->next = head;
        head->prev = n;
    }
    patientCount++;
}

void deleteNode(Node *n) {
    if (n->next == n) {            // only node in the list
        head = NULL;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        if (n == head) head = n->next;
    }
    delete n;
    patientCount--;
}

void printPatient(const Patient &p) {
    cout << "  ID: " << p.id << " | Name: " << p.name << " | Age: " << p.age
         << " | Disease: " << p.disease << " | Bed: " << p.bed << endl;
}

// ---------- Menu functions ----------
void admitPatient() {
    int b = findFreeBed();
    if (b == -1) {
        cout << "No beds available.\n";
        return;
    }
    Patient p;
    cout << "Enter patient ID: ";
    cin >> p.id;
    if (findPatient(p.id) != NULL) {
        cout << "Patient ID already exists.\n";
        return;
    }
    cin.ignore(1000, '\n');
    cout << "Enter name: ";
    cin.getline(p.name, 30);
    cout << "Enter age: ";
    cin >> p.age;
    cin.ignore(1000, '\n');
    cout << "Enter disease: ";
    cin.getline(p.disease, 30);

    p.bed = b + 1;
    beds[b] = 1;
    insertEnd(p);
    cout << "Patient admitted. Bed number " << p.bed << " allotted.\n";
}

void dischargePatient() {
    if (head == NULL) {
        cout << "No patients in the hospital.\n";
        return;
    }
    int id;
    cout << "Enter patient ID to discharge: ";
    cin >> id;
    Node *n = findPatient(id);
    if (n == NULL) {
        cout << "Patient not found.\n";
        return;
    }
    if (queueFull()) {
        Patient old = dequeue();   // oldest record leaves the history to make room
        cout << "(History full: oldest record of " << old.name << " removed from queue.)\n";
    }
    enqueue(n->data);
    beds[n->data.bed - 1] = 0;
    cout << n->data.name << " discharged. Bed " << n->data.bed << " is now free.\n";
    deleteNode(n);
}

void searchPatient() {
    if (head == NULL) {
        cout << "No patients in the hospital.\n";
        return;
    }
    int id;
    cout << "Enter patient ID to search: ";
    cin >> id;
    Node *n = findPatient(id);
    if (n == NULL) cout << "Patient not found.\n";
    else {
        cout << "Patient found:\n";
        printPatient(n->data);
    }
}

void displayForward() {
    if (head == NULL) {
        cout << "No patient records.\n";
        return;
    }
    cout << "Patients (forward, head to tail):\n";
    Node *cur = head;
    do {
        printPatient(cur->data);
        cur = cur->next;
    } while (cur != head);
    cout << "Total patients: " << patientCount << endl;
}

void displayBackward() {
    if (head == NULL) {
        cout << "No patient records.\n";
        return;
    }
    cout << "Patients (backward, tail to head):\n";
    Node *tail = head->prev;
    Node *cur = tail;
    do {
        printPatient(cur->data);
        cur = cur->prev;
    } while (cur != tail);
    cout << "Total patients: " << patientCount << endl;
}

void bedStatus() {
    int freeCount = 0;
    for (int i = 0; i < MAX_BEDS; i++) {
        cout << "  Bed " << i + 1 << ": " << (beds[i] ? "Occupied" : "Free") << endl;
        if (!beds[i]) freeCount++;
    }
    cout << "Free beds: " << freeCount << " / " << MAX_BEDS << endl;
}

// Undo with a queue: the OLDEST discharged patient (front) is re-admitted (FIFO).
void undoDischarge() {
    if (queueEmpty()) {
        cout << "No discharged patients to re-admit.\n";
        return;
    }
    Patient p = dq[qFront];        // peek, do not remove until we know it can be re-admitted
    if (findPatient(p.id) != NULL) {
        cout << "Cannot re-admit: patient ID " << p.id << " is already in use.\n";
        return;
    }
    int b = findFreeBed();
    if (b == -1) {
        cout << "No beds available to re-admit.\n";
        return;
    }
    dequeue();
    p.bed = b + 1;
    beds[b] = 1;
    insertEnd(p);
    cout << p.name << " re-admitted to bed " << p.bed << ".\n";
}

void dischargeHistory() {
    if (queueEmpty()) {
        cout << "Discharge history is empty.\n";
        return;
    }
    cout << "Discharge history (oldest first, front to rear):\n";
    for (int i = 0, idx = qFront; i < qCount; i++, idx = (idx + 1) % QSIZE)
        printPatient(dq[idx]);
}

void freeMemory() {
    while (head != NULL) deleteNode(head);
}

int main() {
    int choice;
    for (int i = 0; i < MAX_BEDS; i++) beds[i] = 0;

    do {
        cout << "\n===== HOSPITAL PATIENT MANAGEMENT SYSTEM =====\n"
             << "1. Admit patient\n"
             << "2. Discharge patient\n"
             << "3. Search patient\n"
             << "4. Display forward\n"
             << "5. Display backward\n"
             << "6. Bed status\n"
             << "7. Undo discharge (re-admit oldest discharged)\n"
             << "8. Discharge history\n"
             << "0. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: admitPatient();     break;
            case 2: dischargePatient(); break;
            case 3: searchPatient();    break;
            case 4: displayForward();   break;
            case 5: displayBackward();  break;
            case 6: bedStatus();        break;
            case 7: undoDischarge();    break;
            case 8: dischargeHistory(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    freeMemory();
    return 0;
}

