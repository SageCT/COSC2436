#include <iostream>

struct node {
    int data;
    node* next;
};

class stack {
    private:
        node* top;
    public:
        stack();
        void push(int val);
        int peek();
        void pop();
        bool isEmpty();
        void print();
};

stack::stack() {
    // constructor
    top = nullptr;
}

void stack::push(int val) {
    // pushes to top of the stack
    node* newNode = new node();
    newNode->data = val;
    newNode->next = top;
    top = newNode;
}

int stack::peek() {
    // if stack is empty, return -1
    // otherwise, return the data of the top of the stack
    if(!isEmpty()) {
        return top->data;
    }
    return -1;
}

void stack::pop() {
    // if stack is not empty, delete the top node of the stack
    if(!isEmpty()) {
        node* temp = top;
        top = top->next;
        delete temp;
    }
}

bool stack::isEmpty() {
    // return true if stack is empty, false otherwise
    return (top == nullptr);
}

void stack::print() {
    // print out every node of the stack
    // cannot traverse using a temp node, must pop
    while(!isEmpty()) {
        std::cout << top->data << " ";
        pop();
    }
}

int main() {
    stack s;
    for(int i = 2; i <= 10; i += 2) {
        s.push(i);
    }

    std::cout << s.peek() << std::endl;

    s.pop();
    s.pop();
    s.pop();

    std::cout << s.peek() << std::endl;

    s.push(20);

    s.print();

    return 0;
}

bool isValid(string s) {
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
            push(s[i]);
        } else {
            if(isEmpty()) {
                return false;
            } else if(s[i] == ')' && peek() == '(') {
                pop();
            } else if(s[i] == '}' && peek() == '{') {
                pop();
            } else if(s[i] == ']' && peek() == '[') {
                pop();
            } else {
                return false;
            }
        }
    }
    if(isEmpty()) {
        return true;
    }
    return false;
}