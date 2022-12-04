#ifndef STACK_H
#define STACK_H

using namespace std;

struct node
{
    int data;
    node *next;
};

class Stack
{
private:
    node *top;

public:
    Stack() : top(nullptr) {}
    void push(int val);
    int peek();
    node *pop();
    bool isEmpty() { return top == nullptr; }
    void print(ostream &);
};

void Stack::push(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = top;
    top = newNode;
}

int Stack::peek()
{
    if (!isEmpty())
        return top->data;

    return -1;
}

node *Stack::pop()
{
    if (!isEmpty())
    {
        node *temp = top;
        top = top->next;
        return temp;
        delete temp;
    }
    return nullptr;
}

void Stack::print(ostream &o)
{
    while (!isEmpty())
    {
        cout << top->data << " ";
        pop();
    }
}

#endif