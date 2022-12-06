#ifndef CLL_H
#define CLL_H

#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class CLL
{
private:
    node *head;
    node *tail;

public:
    CLL() : head(nullptr), tail(nullptr) {}
    node *getHead() { return head; }
    void insertAtHead(int val);
    void insertAtEnd(int val);
    void insertAtPos(int, int);
    void deleteAtHead();
    void deleteAtEnd();
    void deleteByPos(int pos);
    void print(ostream &);
};

void CLL::insertAtHead(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = head;

    head = newNode;
    if (!tail)
        tail = newNode;
    tail->next = head;
}

void CLL::insertAtEnd(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = head;

    if (!head)
        head = tail = newNode;
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    tail->next = head;
}

void CLL::insertAtPos(int val, int pos)
{
    if (pos < 0 || head == nullptr)
        return;
    else if (pos == 0)
        insertAtHead(val);
    else
    {
        node *newNode = new node;
        newNode->data = val;

        node *temp = head;
        do
        {
            if (pos == 1)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                if (temp == tail)
                {
                    newNode = tail;
                }
                break;
            }
            pos--;
            temp = temp->next;
        } while (temp != head);
    }
}

void CLL::deleteAtHead()
{
    if (head)
    {
        node *temp = head;
        if (head->next == head)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            tail->next = head;
        }

        delete temp;
    }
}

void CLL::deleteAtEnd()
{
    if (head)
    {
        if (head->next == head)
        {
            head = tail = nullptr;
        }
        else
        {
            node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            delete temp->next;
            tail = temp;
            tail->next = head;
        }
    }
}

void CLL::deleteByPos(int pos)
{
    if (pos < 0 || head == nullptr)
        return;

    else if (pos == 0)
        deleteAtHead();
    else
    {
        node *prev = head;
        node *cu = head->next;
        while (cu != head)
        {
            if (pos == 1)
            {
                prev->next = cu->next;
                if (cu == tail)
                    tail = prev;
                delete cu;
            }
            pos--;
            prev = cu;
            cu = cu->next;
        }
    }
}

void CLL::print(ostream &o)
{
    if (head)
    {
        node *temp = head;
        do
        {
            o << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
    }
}
#endif