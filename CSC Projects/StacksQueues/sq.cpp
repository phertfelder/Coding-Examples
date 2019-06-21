#include "sq.h"

/**************************************************************************//**
* @author Paul Hertfelder
*
/**************************************************************************/
int main()
{
    push(head, 10);
    
    printList(head);
    return 0;
}

//Push data into stack.
void push(node*& head, int d)
{
    node *temp = new node;
    //first item in stack
    //empty stack
    temp->data = d;
    
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        return;
    }
    //if stack is not empty
    head->next = temp;
    temp->prev = head;
    head = temp;
    
   
    return;

}
//Remove item from stack.
void pop(node*& head)
{
    node *temp = new node;

    //Empty stack.
    if (head == NULL)
    {
        return;
    }
    if (tail == head)
    {
        tail = nullptr;
        head = nullptr;
        return;
    }
    
    temp = head;
    if (head->prev != NULL)
    {
        head = head->prev;
    }
    head->next = nullptr;
    delete temp;
   
    return;
    //Not empty stack.


}
//FIFO queue first in first out
void enqueue(node*& head, int d)
{
    node *temp = new node;
    //first item in stack
    //empty stack
    temp->data = d;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        return;
    }
    //if stack is not empty
    head->next = temp;
    temp->prev = head;
    head = temp;


    return;
}

void dequeue(node*& head)
{

    node *temp = new node;
    if (tail == nullptr)
    {
        return;
    }

    temp = tail;
    if (tail == head)
    {
        tail = nullptr;
        head = nullptr;
        return;
    }
    if (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->prev = nullptr;
    delete temp;
   
  
    return;
}


void printList(node* head)
{
    node *temp = new node;
    int count = 1;
    temp = tail;
        if (head==nullptr && tail==nullptr )
        {
            cout << "Stack is empty." << endl;
            return;
        }

    while (temp->next != nullptr)
    {
        
        cout << temp->data << " ";
        count++;
        temp = temp->next;
    }
    cout << temp->data << endl;

    return;
}