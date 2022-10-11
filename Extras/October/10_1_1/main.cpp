#include <iostream>
#include <fstream>
#include <string>

class stack
{
private:
    int *arr;
    int top;
    int cap;

public:
    stack(int);
    ~stack();

    void push(int);

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return cap == 0; }
    int getSize() const { return size; }
};

stack::stack(int size = 50)
{
    arr = new int[size];
    cap = size;
    top = -1;
}

stack::~stack()
{
    delete[] arr;
}

void stack::push(int v)
{
    if (isFull())
        cout << "Stack is full." << endl;
}

int main()
{

    return 0;
}