#ifndef BST_H
#define BST_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "priQueue.h"

using namespace std;
struct node {
  string val;
  node *left;
  node *right;
};
class BST {
 private:
  node *root;
  string mode;

  void destructorHelper(node *);
  void inOrderTrav(node *) const;
  void preOrderTrav(node *) const;
  void postOrderTrav(node *) const;

 public:
  BST() : root(nullptr), mode("inOrder"){};
  BST(string s) : root(nullptr), mode(s){};
  ~BST();

  bool insert(string s, node *&source);
  void del(string);
  void search(string);

  node *getRoot() const { return root; };
  void setMode(string s) { mode = s; };
  void inOrderTrav(node *) const;
  void preOrderTrav(node *) const;
  void postOrderTrav(node *) const;
  void modeTrav(node *) const;
};

using namespace std;

BST::~BST() {
  if (root != nullptr) destructorHelper(root);
}

void BST::destructorHelper(node *source) {
  if (source == nullptr) return;
  destructorHelper(source->left);
  destructorHelper(source->right);
  delete source;
}

bool BST::insert(string s, node *&source) {
  if (source == nullptr) {
    source = new node();
    source->val = s;
    source->left = nullptr;
    source->right = nullptr;
  }

  if (s.length() < source->val.length()) {
    insert(s, source->left);
  } else if (s.length() > source->val.length()) {
    insert(s, source->right);
  } else if (s.length() == source->val.length()) {
    source->val = s;
  }
}

void BST::inOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  inOrderTrav(cu->left);
  cout << cu->val << " ";
  inOrderTrav(cu->right);
}

void BST::preOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  cout << cu->val << " ";
  preOrderTrav(cu->left);
  preOrderTrav(cu->right);
}

void BST::postOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  postOrderTrav(cu->left);
  postOrderTrav(cu->right);
  cout << cu->val << " ";
}

void BST::modeTrav(node *cu) const {
  if (mode == "inOrder") {
    inOrderTrav(cu);
  } else if (mode == "preOrder") {
    preOrderTrav(cu);
  } else if (mode == "postOrder") {
    postOrderTrav(cu);
  }
}

#endif