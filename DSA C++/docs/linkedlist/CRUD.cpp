//                          TRAVERSAL
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

void traverse(Node* head)
{
    Node* temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void count(Node* head){
    Node* temp = head;
    int count =0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    cout << count << endl;
}

void search (Node* head, int value){
    Node* temp = head;
    while(temp != NULL){
        if(temp->data == value) cout << "found";
        temp = temp->next;
    }
    cout << endl;
}

void insertBegin(Node*& head, int value){
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    Node* temp = head;

    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    
}

void insertEnd(Node*& head, int value){
    Node* newNode = new Node(value);
    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
        cout << "n";
    }
    temp->next = newNode;
    temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;


}

void insertAt(Node*& head, int position, int value){
    Node* newNode = new Node(value);
    Node* temp = head;
    int count = 0;
    while(temp != NULL){
        cout << "count = " << count
     << " data = " << temp->data << endl;
        if(count == position){
            newNode->next = temp->next;
            temp->next = newNode;
            break;
        }
        temp = temp->next;
        count++;
        
        
    }
    
    temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    Node* head = new Node(10);

    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);

    traverse(head);
    count(head);
    search(head, 20);
    insertBegin(head, 100);
    insertEnd(head, 500);
    insertAt(head, 2, 70 );

    return 0;
}