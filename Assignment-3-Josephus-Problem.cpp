// Josephus Problem
// Starts from first person, and alternatively kills the next person. Continues till only one person survives
// Find the position of this person (1-indexed)

// Two Approaches
// 1. Array-based: 1 indicates alive, 0 indicates dead
// 2. Circular Linked List based: just drop the node of the person who was killed

#include <iostream>
using namespace std;

// Array-based solution
int josephusArray(int n, int k) {
    // Create array to track alive (1) and dead (0) people
    int* people = new int[n];
    for(int i = 0; i < n; i++) {
        people[i] = 1;  // all are alive
    }
    
    int alive = n;      
    int count = 0;      // Count for k steps
    int pos = -1;       // Current position
    
    while(alive > 1) {
        // Find next alive person
        do {
            pos = (pos + 1) % n;
        } while(people[pos] == 0);
        
        count++;
        if(count == k) {
            people[pos] = 0;  // Mark as dead
            alive--;
            count = 0;        // Reset counter
        }
    }
    
    // Find the survivor
    for(int i = 0; i < n; i++) {
        if(people[i] == 1) {
            delete[] people;
            return i + 1;     // Convert to 1-indexed
        }
    }
    
    delete[] people;
    return -1;  // Should never reach here
}

// Node for circular linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Linked List based solution
int josephusLinkedList(int n, int k) {
    // Create circular linked list
    Node* head = new Node(1);
    Node* current = head;
    
    // Create n nodes
    for(int i = 2; i <= n; i++) {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head;  // Make it circular
    
    // Keep removing k-th node until only one remains
    Node* prev = current;  // Points to last node
    current = head;
    
    while(current->next != current) { // Stopping condition when the head points to itself
        // Move k-1 steps
        for(int i = 1; i < k; i++) {
            prev = current;
            current = current->next;
        }
        
        // Remove current node
        prev->next = current->next;
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    
    // Get survivor's position
    int result = current->data;
    delete current;
    return result;
}

int main() {
    int n, k = 2;
    cout << "Enter the number of people (n): ";
    cin >> n;
    // cout << "Enter the step size (k): ";
    // cin >> k;
    cout << "\nResults:" << endl;
    cout << "Array-based solution: Person at position " << josephusArray(n, k) << " survives" << endl;
    cout << "Linked List-based solution: Person at position " << josephusLinkedList(n, k) << " survives" << endl;
    
    return 0;
}
