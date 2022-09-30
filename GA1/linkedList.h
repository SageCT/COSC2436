#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct node
{
    T data;
    node<T> *next;
};

template <typename T>
class linkedlist
{
private:
    node<T> *head;
    int size;

public:
    linkedlist();
    ~linkedlist();
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }
    void addAtHead(T value); // Need to add... added
    void addAtTail(T value);
    void removeAtHead(); // Need to add... added
    void removeAtTail();
    void addAtPos(T value, int pos);
    void print(std::ostream &out);
};

using namespace std;

template <typename T>
linkedlist<T>::linkedlist()
{
    head = nullptr;
    size = 0;
}

template <typename T>
linkedlist<T>::~linkedlist()
{
    node<T> *cu = head;
    while (cu != nullptr)
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
    temp->data = value;
    temp->next = head;

    head = temp;
    size++;
}

template <typename T>
void linkedlist<T>::addAtTail(T value)
{
    node<T> *temp = new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T> *cu = head;
    if (cu == nullptr)
    {
        head = temp;
    }
    else
    {
        while (cu->next != nullptr)
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
    if (head == nullptr)
        return;
    else
    {
        delete head;
        head = head->next;
        size--;
    }
}

template <typename T>
void linkedlist<T>::removeAtTail()
{
    node<T> *cu = head;
    node<T> *prev = nullptr;
    if (cu == nullptr)
        return;
    else if (cu->next == nullptr)
    {
        head = nullptr;
    }
    else
    {
        while (cu->next != nullptr)
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = nullptr;
        delete cu;
    }
    size--;
}

template <typename T>
void linkedlist<T>::print(std::ostream &out)
{
    node<T> *cu = head;
    while (cu != nullptr)
    {
        (cu->next == nullptr) ? (out << cu->data) : (out << cu->data << " ");
        cu = cu->next;
    }
}

template <typename T>
void linkedlist<T>::addAtPos(T value, int pos)
{
    node<T> *temp = new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T> *cu = head;
    node<T> *prev = nullptr;

    if (pos > size)
        return;
    else if (pos == 0)
    {
        head = temp;
        temp->next = cu;
    }
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