#include <iostream>
#include <string>
#include <limits> // For std::numeric_limits

using namespace std;

// Define a node structure
struct Node {
    string task;
    Node* next;

    // Constructor to create a new node
    Node(const string& task) : task(task), next(nullptr) {}
};

// Function to insert a task at the end of the list
void addTask(Node*& head, const string& task) {
    Node* newNode = new Node(task);
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

// Function to print all tasks
void viewTasks(Node* head) {
    if (head == nullptr) {
        cout << "Your to-do list is empty!" << endl;
        return;
    }
    Node* temp = head;
    int index = 1;
    while (temp != nullptr) {
        cout << index++ << ". " << temp->task << endl;
        temp = temp->next;
    }
}

// Function to delete a task by position
void deleteTask(Node*& head, int position) {
    if (head == nullptr) {
        cout << "Your to-do list is empty!" << endl;
        return;
    }

    if (position == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < position - 1 && temp->next != nullptr; ++i) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Invalid position!" << endl;
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
}

// Function to delete the entire list and free memory
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Function to clear the screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    Node* head = nullptr;
    int choice, position;
    string task;

    do {
        clearScreen();
        cout << "To-Do List Manager\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer to avoid issues with getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter the task: ";
                getline(cin, task);
                addTask(head, task);
                break;
            case 2:
                viewTasks(head);
                cout << "Press Enter to continue...";
                cin.get(); // Wait for user to press Enter
                break;
            case 3:
                cout << "Enter the task position to delete: ";
                cin >> position;

                // Clear input buffer to avoid issues with getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                deleteTask(head, position);
                cout << "Press Enter to continue...";
                cin.get(); // Wait for user to press Enter
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                cout << "Press Enter to continue...";
                cin.get(); // Wait for user to press Enter
        }
    } while (choice != 4);

    // Clean up memory
    deleteList(head);

    return 0;
}
/*
Node Structure: A struct Node representing each task in the to-do list. Each node contains a string task and a pointer next to the next node.
addTask Function: Adds a new task to the end of the list.
viewTasks Function: Displays all tasks in the to-do list.
deleteTask Function: Deletes a task by its position in the list.
deleteList Function: Frees the memory allocated for the list nodes.
main Function: Provides a menu-driven interface for the user to interact with the to-do list manager.

Input Handling: Used cin.ignore() with numeric_limits<streamsize>::max() to clear the input buffer after reading an integer choice. This ensures that the next input operation works correctly.
Clear Screen: Added the clearScreen() function to clear the screen. It uses system("cls") for Windows and system("clear") for other systems.
User Prompts: Added prompts to press Enter to continue after viewing tasks and deleting tasks. This allows the user to see the output before the screen is cleared.
*/
