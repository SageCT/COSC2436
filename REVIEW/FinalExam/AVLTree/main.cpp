#include <iostream>
#include <stack>

#include "AVL.h"

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *n)
{
    return !n ? 0 : n->height;
}

Node *rightRotate(Node *n)
{
    Node *x = n->left;
    Node *T2 = x->right;
    x->right = n;
    n->left = T2;
    n->height = max(height(n->left), height(n->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
}

class Queue
{
private:
    stack<int> s1, s2;

public:
    void push(int x);
    void enq(int x);
};

void Queue::enq(int x)
{
    if (!s2.empty())
    {
        while (!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    s1.push(x);
    while (!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
}

int main()
{
    Node *root = nullptr;
    root = insertNode(root, 5);
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 5);
    printTree(root, "", true);
}