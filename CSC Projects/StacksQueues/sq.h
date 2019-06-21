#ifndef _sq_H_
#define _sq_H_
#include <iostream>

using namespace std;
//FILO/LIFO for stack
// functions needed:
struct node;
void push(node*& head, int d);
void pop(node*& head);
void printList(node* head);
void enqueue(node*& head, int d);

//FIFO for queue.
void dequeue(node*& head);

struct node
{
    int data=NULL;
    node *prev=  nullptr;
    node *next = nullptr;
    

};
node *head;
node *tail;

#endif  