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
  node *root;

  int getBalance(node *);
  int height(node *);
  node *newNode(int);
  node *leftRotate(node *);
  node *rightRotate(node *);
  node *insertHelper(node *, int);
  node *balanceTree(node *);
  void printLevel(node *root, ostream &o, int level, bool);

 public:
  Tree() { root = nullptr; };
  ~Tree();
  node *insert(node *node, int key);
  node *remove(node *root, int key);
  node *getMinimum(node *) const;
  node *getRoot() const { return root; };
  void print(node *, std::ostream &);
};

Tree::~Tree() {
  while (root != nullptr) {
    root = remove(root, root->key);
  }
  delete root;
}

int Tree::height(node *n) {
  if (n == nullptr) return 0;
  return n->height;
}

node *Tree::newNode(int key) {
  node *n = new node;
  n->key = key;
  n->left = nullptr;
  n->right = nullptr;
  n->height = 1;
  return n;
}

int Tree::getBalance(node *n) {
  if (n == nullptr) return 0;
  return height(n->left) - height(n->right);
}

// Return node with smallest value in tree, from node
node *Tree::getMinimum(node *n) const {
  node *current = n;
  while (current->left != nullptr) current = current->left;
  return current;
}

node *Tree::leftRotate(node *x) {
  node *y = x->right;
  node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

node *Tree::rightRotate(node *y) {
  node *x = y->left;
  node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

node *Tree::balanceTree(node *n) {}

node *Tree::insert(node *node, int key) {
  root = insertHelper(node, key);
  return root;
}

node *Tree::insertHelper(node *node, int key) {
  // Find the correct position and insert the node
  if (node == nullptr) return newNode(key);
  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  // Update the balance factor of each node and balance the tree
  node->height = max(height(node->left), height(node->right)) + 1;
  int BF = getBalance(node);
  if (BF > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }

  if (BF < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

node *Tree::remove(node *root, int key) {
  // Find the node to delete and remove it
  if (root == nullptr) return root;
  if (key < root->key)
    root->left = remove(root->left, key);
  else if (key > root->key)
    root->right = remove(root->right, key);
  else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      node *temp = root->left ? root->left : root->right;
      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else
        *root = *temp;
      delete temp;
    } else {
      node *temp = getMinimum(root->right);
      root->key = temp->key;
      root->right = remove(root->right, temp->key);
    }
  }

  if (root == nullptr) return root;

  // Updte the balace factor of each node and balance the tree
  root->height = max(height(root->left), height(root->right)) + 1;
  int BF = getBalance(root);
  if (BF > 1) {
    if (getBalance(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (BF < -1) {
    if (getBalance(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

void Tree::printLevel(node *root, std::ostream &o, int level, bool firstEntry) {
  if (root == nullptr) return;
  if (level == 1)
    firstEntry ? o << root->key : o << " " << root->key;
  else if (level > 1) {
    printLevel(root->left, o, level - 1, false);
    printLevel(root->right, o, level - 1, false);
  }
}

void Tree::print(node *root, std::ostream &o) {
  int h = height(root);
  bool lastEntry = false;
  for (int i = 1; i <= h; i++) {
    i == 1 ? printLevel(root, o, i, true) : printLevel(root, o, i, false);
  }
}

#endif