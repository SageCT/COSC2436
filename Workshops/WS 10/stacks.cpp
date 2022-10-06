#include <iostream>

struct node
{
    int data;
    node *next;
};

class stack
{
private:
    node *top;

public:
    stack();
    void push(int val);
    int peek();
    void pop();
    bool isEmpty();
    void print();
};

stack::stack()
{
    // constructor
    top = new node();
}

void stack::push(int val)
{
    // pushes to top of the stack

    if (isEmpty())
    {
        node *t = new node();
        t->data = val;
        t->next = nullptr;
        top = t;
        delete t;
    }

    else
    {
        node *t = new node();
        t->data = val;
        t->next = top;

        top = t;
    }
}

int stack::peek()
{
    // if stack is empty, return -1
    // otherwise, return the data of the top of the stack
    if (isEmpty())
        return -1;

    return top->data;
}

void stack::pop()
{
    // if stack is not empty, delete the top node of the stack
    if (!isEmpty() && top->next != nullptr)
    {
        node *temp = new node();
        temp = top;
        top = top->next;

        delete temp;
    }
    else if (top->next == nullptr)
    {
    }
}

bool stack::isEmpty()
{
    // return true if stack is empty, false otherwise
    bool empty;
    (top == nullptr) ? (empty = true) : (empty = false);
    return empty;
}

void stack::print()
{
    // print out every node of the stack
    // cannot traverse using a temp node, must pop
    while (!isEmpty())
    {
        std::cout << peek() << std::endl;
        pop();
    }
}

int main()
{
    stack s;
    s.print();
    for (int i = 2; i <= 10; i += 2)
    {
        s.push(i);
    }

    // std::cout << s.peek() << std::endl;

    // s.pop();
    // s.pop();
    // s.pop();

    // std::cout << s.peek() << std::endl;

    // s.push(20);

    s.print();

    return 0;
}