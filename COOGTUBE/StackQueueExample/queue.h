#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class queue
{
private:
    node *front;
    node *tail;

public:
    queue() : front(nullptr), tail(nullptr) {}
    void enqueue(int val);
    int peek();
    int dequeue();
    bool isEmpty() { return front == nullptr; }
    void print(ostream &);
};

void queue::enqueue(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = nullptr;

    if (isEmpty())
        front = tail = newNode;
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

int queue::dequeue()
{
    if (!isEmpty())
    {
        node *temp = front;
        front = front->next;
        return temp->data;
        delete temp;
    }
    return -1;
}

void queue::print(ostream &o)
{
    while (front)
        o << dequeue() << " ";
}

#endif