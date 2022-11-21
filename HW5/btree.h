#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct node {
  int *keys;
  node **childptr;
  node *parentptr;
  bool leaf;
  int size;

  node(int degree) {
    keys = new int[degree];
    childptr = new node *[degree + 1];
    parentptr = nullptr;
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) keys[i] = -1;
    for (int i = 0; i < degree + 1; i++) childptr[i] = nullptr;
  }

  node(node *parent, int degree) {
    keys = new int[degree];
    childptr = new node *[degree + 1];
    parentptr = parent;
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) keys[i] = -1;
    for (int i = 0; i < degree + 1; i++) childptr[i] = nullptr;
  }
};

class btree {
 private:
  node *root;
  int degree;

  node *printLevel(node *n, int level, ostream &out) {
    if (n == nullptr) return nullptr;
    if (n->leaf && level == 1) {
      for (int i = 0; i < n->size; i++) {
        out << n->keys[i] << " ";
      }
    } else if (level > 1) {
      printLevel(n->childptr[0], level - 1, out);
      printLevel(n->childptr[n->size], level - 1, out);
    }
  }

 public:
  btree(int _degree) {
    root = nullptr;
    degree = _degree;
  }

  // Inserts a node into the B-tree, if root is nullptr, adds at leaf
  void insert(int data) {
    if (root == nullptr) {
      root = new node(degree);
      root->keys[0] = data;
      root->size = 1;
    } else {
      addAtLeaf(nullptr, root, data);
    }
  }

  // Adds the new node into the tree at first available leaf,
  // if leaf is full uses splitChild to create a new array
  void addAtLeaf(node *parent, node *n, int data) {
    // If n is a leaf
    if (n->leaf) {
      int i = n->size;
      // Find the first spot where data is less than keys[i]
      while (i != 0 && data < n->keys[i - 1]) {
        n->keys[i] = n->keys[i - 1];
        i--;
      }
      n->keys[i] = data;
      n->parentptr = parent;
      n->size++;
    } else {
      int i = 0;
      while (i < n->size && data > n->keys[i]) {
        i++;
      }
      addAtLeaf(n, n->childptr[i], data);
    }
    if (n->size == degree) {
      //   split(parent, n);
      if (n == root) {
        node *temp = new node(degree);
        temp->leaf = false;
        temp->childptr[0] = n;
        splitChild(temp, n);
        root = temp;
      } else {
        splitChild(parent, n);
      }
    }
  }

  // n is a full child, split it into two children with parent as the new
  // parent node
  void splitChild(node *parent, node *leftNode) {
    // Passed as left, so create right node
    node *rightNode = new node(degree);
    int mid = (degree - 1) / 2;

    // Copy half of left node keys to right node keys
    // Copy half the pointer of left node to right node
    int firstLeft, firstRight;
    for (int x = 0; x <= mid; x++) {
      rightNode->keys[x] = leftNode->keys[x + (mid + 1)];
      rightNode->childptr[x] = leftNode->childptr[x + (mid + 1)];
      rightNode->size++;
    }

    // Store the first key of the nodes to find where it fits in with the
    // parent node
    firstLeft = leftNode->keys[0], firstRight = rightNode->keys[0];
    // Find the correct position to add the new array
    for (int i = 0; i < parent->size; i++) {
      if (firstLeft < parent->keys[i]) {
        for (int j = parent->size; j > i; j--) {
          parent->keys[j] = parent->keys[j - 1];
          parent->childptr[j + 1] = parent->childptr[j];
        }
        parent->keys[i] = firstRight;
        parent->childptr[i + 1] = rightNode;
        parent->size++;
        break;
      }
    }

    // Add the middle key to the parent node
  }

  void printLevel(int level, ostream &out) { printLevel(root, level, out); }
};

#endif