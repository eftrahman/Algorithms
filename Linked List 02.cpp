#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    // Constructor to easily create a new node
    Node(int val) : data(val), next(nullptr) {}
};

// Function to insert a node at the end of the list
void insertAtEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

// Function to delete the linked list and free memory
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    int n, value;

    cout << "Enter the number of elements you want to insert: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter value for element " << i + 1 << ": ";
        cin >> value;
        insertAtEnd(head, value);
    }

    cout << "The linked list is: ";
    printList(head);

    // Clean up memory
    deleteList(head);

    return 0;
}
/*
1.Node Structure: Each node has an integer data and a pointer to the next node.
2.LinkedList Class:
    -head: A pointer to the first node in the list.
    -insertAtBeginning(int val): Creates a new node and inserts it at the beginning.
    -insertAtEnd(int val): Creates a new node and inserts it at the end.
    -deleteNode(int val): Deletes the node with the specified value.
    -printList() const: Prints the entire list.
    -Destructor: Frees all nodes when the linked list object is destroyed.
*/
