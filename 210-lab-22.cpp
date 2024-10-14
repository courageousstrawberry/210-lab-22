#include <iostream>
using namespace std;
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
class DoublyLinkedList
{
private:
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node *head;
    Node *tail;

public:
    // constructor
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    void push_back(int value)
    {
        Node *newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void push_front(int value)
    {
        Node *newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insert_after(int value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }
    void delete_node(int value)
    {
        if (!head)
            return; // Empty list
        Node *temp = head;
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp)
            return; // Value not found
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Deleting the head
        }
        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }
    // Delete node by position.
    void delete_pos(int pos) {
        int count = 0;
        if (!head){
            return;
        }
        Node *temp = head;
        if (pos == 0) {
            head = head->next;
            // Check if there is a value in head
            if (head) {
                head->prev = nullptr
            }
            delete temp;
            return;
        }
        // Loop through the linked list, until correct position is reached.
        while(temp && count != pos){
            temp = temp->next;
            count++;
        }
        // If temp reaches the end of the list, end the function.
        if (temp == nullptr) {
            return;
        }

        // Rearrange the pointers surrounding the node at the position to delete.
        if(temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }
        // If position is the tail
        if (temp == tail) {
            tail = temp->prev;
        }
        delete temp;
    }
    void pop_front() {
        if (!head){
            return;
        }
        Node *temp = head;
        head = head->next;
        // Check if head still exists and update the prev value.
        if(head) {
            head->prev = nullptr;
        }
        else {
            // If head doesn't exist, the list is now empty
            tail = nullptr;
        }
        delete temp;
        temp = nullptr;
    }
    void pop_back() {
        if (!head) {
            return;
        }
        // Check if list only has one node
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        // Go to last node
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        temp = nullptr;
    }
    void print()
    {
        Node *current = head;
        if (!current)
            return;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    void print_reverse()
    {
        Node *current = tail;
        if (!current)
            return;
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
// Driver program
int main()
{
    DoublyLinkedList list;
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    return 0;
}
