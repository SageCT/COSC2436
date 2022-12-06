#ifndef DLL_H
#define DLL_H

#include <iostream>
using namespace std;

struct node
{
    int val;
    node *next;
    node *prev;
};

class DLL
{
private:
    node *head;
    node *tail;
    int size;

public:
    DLL() : head(nullptr), tail(nullptr), size(0) {}
    ~DLL();
    void addToHead(int);
    void addToPos(int, int);
    void reverse();
    void print();
    void printFromTail();
};

DLL::~DLL()
{
    node *cu = nullptr;
    while (head)
    {
        cu = head;
        head = head->next;
        delete cu;
    }
}

void DLL::addToHead(int value)
{
    node *temp = new node;
    temp->val = value;
    temp->next = temp->prev = nullptr;
    if (!head)
        head = tail = temp;
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    size++;
}

void DLL::addToPos(int value, int pos)
{
    node *temp = new node;
    temp->val = value;
    temp->next = temp->prev = nullptr;

    if (pos > size)
        return;
    else if (pos != 0)
    {
        node *cu = head;
        for (int i = 1; i < pos; i++)
        {
            cu = cu->next;
        }
        temp->next = cu->next;
        temp->prev = cu->prev;
        cu->next->prev = temp;
        cu->next = temp;
    }
    else
        addToHead(value);

    size++;
}

void DLL::reverse()
{
    node *cu = head;
    node *prev = nullptr;

    while (cu)
    {
        prev = cu->prev;
        if (!prev)
            tail = cu;

        cu->prev = cu->next;
        cu->next = prev;
        head = cu;
        cu = cu->prev;
    }
}

void DLL::print()
{
    if (!head)
    {
        cout << "Empty\n";
        return;
    }

    cout << "Printing from head:\n";
    node *cu = head;
    while (cu)
    {
        cout << cu->val << " ";
        cu = cu->next;
    }
    cout << '\n';
}

#endif