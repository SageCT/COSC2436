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

  void inOrderTrav(node *, ofstream &);
  void preOrderTrav(node *, ofstream &);
  void postOrderTrav(node *, ofstream &);
  void insert(string s, node *&source);

 public:
  BST() : root(nullptr), mode("inOrder"){};
  BST(string s) : root(nullptr), mode(s){};
  ~BST();

  void del(string);
  void search(string);
  void insert(string s) { insert(s, root); }

  node *getRoot() const { return root; };
  void setMode(string s) { mode = s; };
  void inOrderTrav(ofstream &o) { inOrderTrav(root, o); };
  void preOrderTrav(ofstream &o) { preOrderTrav(root, o); };
  void postOrderTrav(ofstream &o) { postOrderTrav(root, o); };
};

BST::~BST() {
  if (root != nullptr) destructorHelper(root);
}

void BST::destructorHelper(node *source) {
  if (source == nullptr) return;
  destructorHelper(source->left);
  destructorHelper(source->right);
  delete source;
}

void BST::insert(string s, node *&source) {
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

void BST::inOrderTrav(node *cu, ofstream &o) {
  if (cu == nullptr) return;
  inOrderTrav(cu->left, o);
  o << cu->val << " ";
  inOrderTrav(cu->right, o);
}

void BST::preOrderTrav(node *cu, ofstream &o) {
  if (cu == nullptr) return;
  o << cu->val << " ";
  preOrderTrav(cu->left, o);
  preOrderTrav(cu->right, o);
}

void BST::postOrderTrav(node *cu, ofstream &o) {
  if (cu == nullptr) return;
  postOrderTrav(cu->left, o);
  postOrderTrav(cu->right, o);
  o << cu->val << " ";
}


#endif