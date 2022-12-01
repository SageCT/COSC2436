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

  void inOrderTrav(node *, vector<string> &v);
  void preOrderTrav(node *, vector<string> &v);
  void postOrderTrav(node *, vector<string> &v);
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
  string getMode() const { return mode; };
  void inOrderTrav(vector<string> &v) { inOrderTrav(root, v); };
  void preOrderTrav(vector<string> &v) { preOrderTrav(root, v); };
  void postOrderTrav(vector<string> &v) { postOrderTrav(root, v); };
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

void BST::inOrderTrav(node *cu, vector<string> &v) {
  if (cu == nullptr) return;
  inOrderTrav(cu->left, v);
  v.push_back(cu->val);
  inOrderTrav(cu->right, v);
}

void BST::preOrderTrav(node *cu, vector<string> &v) {
  if (cu == nullptr) return;
  v.push_back(cu->val);
  preOrderTrav(cu->left, v);
  preOrderTrav(cu->right, v);
}

void BST::postOrderTrav(node *cu, vector<string> &v) {
  if (cu == nullptr) return;
  postOrderTrav(cu->left, v);
  postOrderTrav(cu->right, v);
  v.push_back(cu->val);
}

#endif