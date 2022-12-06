#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
struct node
{
    T val;
    node *next;
};
template <typename T>
class linkedlist
{
private:
    node<T> *head;
    int size;

public:
    linkedlist() : head(nullptr), size(0) {}
    ~linkedlist();
    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }
    node<T> *getHead() const { return head; }
    void addAtHead(T value);
    void addAtTail(T value);
    void removeAtHead();
    void removeAtTail();
    void removeAtPos(int pos);
    void addAtPos(T value, int pos);
    node<T> *returnAtPos(int pos);
    int search(string toFind) const;
    void swap(node<T> *n1, node<T> *n2);
    void print(ostream &out);
};

template <typename T>
linkedlist<T>::~linkedlist()
{
    node<T> *cu = head;
    while (cu)
    {
        node<T> *temp = cu;
        cu = cu->next;
        delete temp;
    }
}

template <typename T>
void linkedlist<T>::addAtHead(T value)
{
    node<T> *temp = new node<T>();
    temp->val = value;
    temp->next = head;

    head = temp;
    size++;
}

template <typename T>
void linkedlist<T>::addAtTail(T value)
{
    node<T> *temp = new node<T>();
    temp->val = value;
    temp->next = nullptr;

    node<T> *cu = head;

    // if cu == nullptr
    if (!cu)
    {
        head = temp;
    }
    else
    {
        while (cu->next)
        {
            cu = cu->next;
        }
        cu->next = temp;
    }
    size++;
}

template <typename T>
void linkedlist<T>::removeAtHead()
{
    if (!head)
        return;
    else
    {
        delete head;
        head = head->next;
        size--;
    }
}

template <typename T>
void linkedlist<T>::removeAtPos(int pos)
{
    int currIndex = 0;
    node<T> *curr = head;
    node<T> *prev = nullptr;
    node<T> *next = head->next;

    if (pos == 0)
        removeAtHead();
    else
    {
        while (currIndex < pos)
        {
            prev = curr;
            next = next->next;
            curr = curr->next;
            currIndex++;
        }
        if (currIndex == pos)
        {
            prev->next = next;
            curr->next = nullptr;
            delete curr;
        }
        size--;
    }
}

template <typename T>
void linkedlist<T>::addAtPos(T value, int pos)
{
    node<T> *temp = new node<T>();
    temp->val = value;
    temp->next = nullptr;

    node<T> *cu = head;
    node<T> *prev = nullptr;

    if (pos == 0)
    {
        head = temp;
        temp->next = cu;
    }
    else if (pos > size)
        return;
    else
    {
        for (int i = 0; i < pos; i++)
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;
        temp->next = cu;
    }
    size++;
}

template <typename T>
node<T> *linkedlist<T>::returnAtPos(int pos)
{
    node<T> *cu = head;
    while (pos > 0)
    {
        cu = cu->next;
        pos--;
    }

    return cu;
}

template <typename T>
void linkedlist<T>::print(ostream &out)
{
    node<T> *cu = head;
    while (cu)
    {
        (!cu->next) ? (out << cu->val) : (out << cu->val << endl);
        cu = cu->next;
    }
}

#endif