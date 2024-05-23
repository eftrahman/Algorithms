#include <iostream>
#include <fstream>
#include <string>
#include <limits>

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

// Function to load tasks from a file
void loadTasks(Node*& head, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string task;
        while (getline(file, task)) {
            addTask(head, task);
        }
        file.close();
    }
}

// Function to save tasks to a file
void saveTasks(Node* head, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Node* temp = head;
        while (temp != nullptr) {
            file << temp->task << endl;
            temp = temp->next;
        }
        file.close();
    }
}

int main() {
    Node* head = nullptr;
    int choice, position;
    string task;
    const string filename = "todo_list.txt";

    // Load tasks from file
    loadTasks(head, filename);

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

    // Save tasks to file
    saveTasks(head, filename);

    // Clean up memory
    deleteList(head);

    return 0;
}

