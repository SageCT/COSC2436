#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
struct node
{
    T data;
    node<T> *next;
};

template <typename T>
class queue
{
private:
    node<T> *head, *tail;
    int size;

public:
    queue();
    ~queue();
    bool isEmpty() const { return head == nullptr; };
    int getSize() const { return size; };
    node<T> peek() const { return head; };
    void enqueue(T);
    node<T> *dequeue();
    void print(std::ostream &out);
};

template <typename T>
queue<T>::queue()
{
    int size = 0;
    head = tail = nullptr;
}

template <typename T>
queue<T>::~queue()
{
    while (!isEmpty())
        dequeue();
}

template <typename T>
void queue<T>::enqueue(T val)
{
    node<T> *toAdd;
    toAdd->data = val;

    if (isEmpty())
    {
        head = tail = toAdd;
    }
    else
    {
        tail->next = toAdd;
        tail = toAdd;
    }
}

template <typename T>
node<T> *queue<T>::dequeue()
{
    if (isEmpty())
        return head;
    else
    {
        node<T> *temp;
        temp = head;
        head = head->next;
        delete head;
        return temp;
    }
}

template <typename T>
void queue<T>::print(std::ostream &out)
{
    while (!isEmpty())
    {
        out << dequeue()->data << endl;
    }
}
