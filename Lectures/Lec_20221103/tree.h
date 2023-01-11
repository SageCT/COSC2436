#include <iostream>

struct node {
  node *left;
  int val;
  node *right;
};

class tree {
 private:
  node *root;

 public:
  tree() { root = nullptr; };
  void insert(int);
  void del(int);
  void search(int);
  node *getRoot() const { return root; };
  void inOrderTrav(node *) const;
  void preOrderTrav(node *) const;
  void postOrderTrav(node *) const;
};

using namespace std;

void tree::postOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  postOrderTrav(cu->left);
  postOrderTrav(cu->right);
  cout << cu->val << " ";
}

void tree::preOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  cout << cu->val << " ";
  preOrderTrav(cu->left);
  preOrderTrav(cu->right);
}

void tree::inOrderTrav(node *cu) const {
  if (cu == nullptr) return;
  inOrderTrav(cu->left);
  cout << cu->val << " ";
  inOrderTrav(cu->right);
}