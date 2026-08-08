#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int val)
    {
        data = val;
        next = nullptr;
    }
};

// Reverse Function
Node* reverse(Node* head)
{
    Node* prev = NULL;
    Node* curr = head;
    

    while(curr != NULL ){
        Node* nexts = curr->next;
        curr->next = prev;

        prev = curr;
        curr = nexts;
    }

    return prev;   // Return the new head
}

// Print Function
void print(Node* head)
{
    Node* temp = head;

    while(temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    // Creating Linked List
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    head->next->next->next->next = new Node(50);

    cout << "Original: ";
    print(head);

    // Reverse Linked List
    head = reverse(head);

    cout << "After Reverse: ";
    print(head);

    return 0;
}