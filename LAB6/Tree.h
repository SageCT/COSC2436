#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct node {
  T val;
  node<T> *left;
  node<T> *right;
};

template <typename T>
class Tree {
 private:
  int size;

 public:
};

#endif