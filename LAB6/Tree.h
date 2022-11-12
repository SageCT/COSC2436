#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct node {
  int key;
  node *left;
  node *right;
  int height;
};

class Tree {
 private:
  int size;
  node *root;

  int getBalance(node *);
  int height(node *);
  node *newNode(int);
  node *leftRotate(node *);
  node *rightRotate(node *);

 public:
  Tree() : size(0) { root = nullptr; };
  ~Tree();
  node *insert(node *node, int key);
  node *deletenode(node *root, int key);
};

int height(node *n) {
  if (n == nullptr) return 0;
  return n->height;
}

node *newNode(int key) {
  node *n = new node;
  n->key = key;
  n->left = nullptr;
  n->right = nullptr;
  n->height = 1;
  return n;
}

int getBalance(node *n) {
  if (n == nullptr) return 0;
  return height(n->left) - height(n->right);
}

node *leftRotate(node *x) {
  node *y = x->right;
  node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

node *rightRotate(node *y) {
  node *x = y->right;
  node *T2 = x->left;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

#endif