#ifndef BTREE2_H
#define BTREE2_H

#include <iostream>
using namespace std;

class Node {
  int *keys;
  Node **childPtr;
  int degree;
  int size;
  bool leaf;

 public:
  Node(int, bool);

  void insertNonFull(int);
  void splitChild(int, Node *);
  void traverse(int level, ostream &o);
  void printLevel(int level, ostream &o);

  friend class BTree;
};

class BTree {
  Node *root;
  int degree;

 public:
  BTree(int d) {
    root = nullptr;
    degree = d;
  }

  void printLevel(int level, ostream &o) {
    if (root != nullptr) root->traverse(level, o);
  }

  void insert(int);
};

/* Defining Node functions */

// Node constructor
Node::Node(int d, bool l) {
  // Set the degree, leaf boolean, and initalize the keys and child ptrs
  degree = d, leaf = l;
  keys = new int[2 * degree - 1];
  childPtr = new Node *[2 * degree];

  size = 0;
}

// Traverses the nodes, level by level
void Node::traverse(int level, ostream &o) {
  int i;
  for (i = 0; i < size; i++) {
    if (!leaf) childPtr[i]->traverse(level, o);
    o << " " << keys[i];
  }
  if (!leaf) childPtr[i]->traverse(level, o);
}

void Node::printLevel(int level, ostream &o) {
  int i;
  for (i = 0; i < size; i++) {
    if (!leaf) childPtr[i]->printLevel(level - 1, o);
    o << " " << keys[i];
  }
  if (!leaf) childPtr[i]->printLevel(level, o);
}

/* End Node functions */

/* Define BTree functions */

void BTree::insert(int key) {
  if (root == nullptr) {
    root = new Node(degree, true);
    root->keys[0] = key;
    root->size = 1;
  } else {
    if (root->size == 2 * degree - 1) {
      Node *s = new Node(degree, false);
      s->childPtr[0] = root;
      s->splitChild(0, root);
      int i = 0;
      if (s->keys[0] < key) i++;
      s->childPtr[i]->insertNonFull(key);

      // Update root with new root
      root = s;
    } else
      root->insertNonFull(key);
  }
}

// Insert if the node is empty
void Node::insertNonFull(int key) {
  int i = size - 1;

  if (leaf) {
    while (i >= 0 && keys[i] > key) keys[i + 1] = keys[i--];

    keys[i + 1] = key;
    size++;
  } else {
    while (i >= 0 && keys[i] > key) i--;

    if (childPtr[i + 1]->size == 2 * degree - 1) {
      splitChild(i + 1, childPtr[i + 1]);

      if (keys[i + 1] < key) i++;
    }

    childPtr[i + 1]->insertNonFull(key);
  }
}

// Split Child Node
void Node::splitChild(int i, Node *leftNode) {
  Node *rightNode = new Node(leftNode->degree, leftNode->leaf);
  rightNode->size = degree - 1;

  for (int x = 0; x < degree - 1; x++)
    rightNode->keys[x] = leftNode->keys[x + degree];

  if (!leftNode->leaf)
    for (int x = 0; x < degree; x++)
      rightNode->childPtr[x] = leftNode->childPtr[x + degree];

  leftNode->size = degree - 1;
  for (int x = size; x >= i + 1; x--) childPtr[x + 1] = childPtr[x];

  childPtr[i + 1] = rightNode;

  for (int x = size - 1; x >= i; x--) keys[x + 1] = keys[x];

  keys[i] = leftNode->keys[degree - 1];
  size++;
}

/* End BTree functions */

#endif