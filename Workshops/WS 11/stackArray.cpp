#include <iostream>

class stackArray
{
private:
    int *arr;
    int size;
    int top;

public:
    stackArray();
    bool isEmpty();
    bool isFull();
    void resize();
    void push(int value);
    void pop();
    int peek();
    void print();
};

stackArray::stackArray()
{
    // implement
    // let's initialize size to 3

    size = 3, top = -1;
    arr = new int[3];
}

bool stackArray::isEmpty()
{
    // implement
    return top == -1;
}

bool stackArray::isFull()
{
    // implement
    return top == size - 1;
}

void stackArray::resize()
{
    // implement
    int *temp = new int[size + 10];

    for (int x = 0; x < size; x++)
    {
        temp[x] = arr[x];
    }

    arr = temp;
}

void stackArray::push(int value)
{
    // implement
    if (isFull())
        resize();
    else
        arr[++top] = value;
}

void stackArray::pop()
{
    // implement
    if (!isEmpty())
        top--;
}

int stackArray::peek()
{
    // implement
    return arr[top];
}

void stackArray::print()
{
    // implement
    if (!isEmpty())
        for (int x = 0; x < size; x++)
            (x != size - 1) ? (std::cout << arr[x] << " ") : (std::cout << arr[x] << std::endl);
}

int main()
{
    stackArray s;

    s.push(10);
    s.push(20);
    s.pop();

    s.push(30);
    s.push(40);
    s.pop();

    s.push(55);
    std::cout << s.peek() << std::endl;

    s.push(60);

    s.print();

    return 0;
}