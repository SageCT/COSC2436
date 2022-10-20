#include <iostream>

class queueArray
{
private:
    int *arr;
    int size;
    int front, end;

public:
    queueArray();
    bool isEmpty();
    bool isFull();
    void resize();
    void enqueue(int value);
    void dequeue();
    int peek();
    void print();
};

queueArray::queueArray()
{
    // implement
    // lets initialize size to 3
    end = 1, front = 0, size = 0;
    arr = new int[3];
}

bool queueArray::isEmpty()
{
    // implement
    return front == 0 && end == 1;
}

bool queueArray::isFull()
{
    // implement
    return end == size - 1;
}

void queueArray::resize()
{
    // implement
}

void queueArray::enqueue(int value)
{
    // implement
}

void queueArray::dequeue()
{
    // implement
}

int queueArray::peek()
{
    // implement
}

void queueArray::print()
{
    // implement
}

int main()
{
    queueArray q;

    // q.enqueue(10);
    // q.enqueue(20);
    // q.enqueue(30);
    // q.enqueue(40);
    // q.dequeue();
    // q.dequeue();

    // q.enqueue(50);
    // std::cout << q.peek() << std::endl;

    // q.print();

    return 0;
}