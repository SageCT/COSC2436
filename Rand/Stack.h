#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

// This file is provided to assist with the hw, but you can change or implement the solution in your own way.
// Hint: use stack to shift the matrix.

struct sNode {
  char data;
  sNode *next;
};

class Stack {
private:
  sNode *top;
  int size;

public:
  Stack();
  bool isEmpty();
  void push(char);
  char pop();
  char peek();
  int getSize();
};

Stack::Stack() {
  top = nullptr;
  size = 0;
}

bool Stack::isEmpty() { return (top == nullptr); }

void Stack::push(char x) {
  sNode *temp = new sNode();
  temp->data = x;
  temp->next = top;
  top = temp;
  size++;
}

char Stack::pop() {
  int temp = top->data;
  sNode *del = top;
  top = top->next;
  delete del;
  size--;
  return temp;
}

char Stack::peek() { return top->data; }

int Stack::getSize() { return size; }

#endif