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
  void traverse();

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

  void traverse() {
    if (root != nullptr) root->traverse();
  }

  void insert(int);
};

// Node constructor
Node::Node(int d, bool l) { degree = d, leaf = l; }

#endif