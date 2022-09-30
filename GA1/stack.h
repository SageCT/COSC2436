#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class stack
{
private:
    int size;
    node<T> *head , *tail;

public:
    stack();
    ~stack();
    bool isEmpty() const { return head == nullptr; };
    int getSize() const { return size; };
    void push(T);
    T pop();
    T peek() const;
};

template <typename T>
stack<T>::stack()
{
    head = tail = nullptr;
    size = 0;
}

template <typename T>
stack<T>::~stack()
{
   
}

template <typename T>
void stack<T>::push(T val)
{
    
}

template <typename T>
T stack<T>::pop()
{
}

template <typename T>
T stack<T>::peek() const
{
}