#include <algorithm>
#include <iostream>

struct node {
  int val;
  node* left;
  node* right;
};

class BST {
 private:
  node* root;
  void destructorHelper(node*);
  bool insert(int const, node*&);
  node* getNode(int const, node*);
  int getDepth(int const, node*);
  void printPreOrder(node*);
  void printInOrder(node*);
  void printPostOrder(node*);

 public:
  BST() { root = nullptr; }
  ~BST();
  bool insert(int const V) { return insert(V, root); }
  bool isEmpty() { return root == nullptr; }
  node* getRoot() { return root; }
  node* getNode(int const V) { return getNode(V, root); }
  int getHeight(node*);
  int getDepth(int const V) { return getDepth(V, root); }
  void printPreOrder() { printPreOrder(root); }
  void printInOrder() { printInOrder(root); }
  void printPostOrder() { printPostOrder(root); }
};

BST::~BST() {
  if (root != nullptr) destructorHelper(root);
}

void BST::destructorHelper(node* source) {
  if (source == nullptr) return;
  destructorHelper(source->left);
  destructorHelper(source->right);
  delete source;
}

bool BST::insert(int const value, node*& source) {
  if (source == nullptr) {
    source = new node();
    source->val = value;
    source->left = nullptr;
    source->right = nullptr;
  }

  if (value < source->val) {
    insert(value, source->left);
  } else if (value > source->val) {
    insert(value, source->right);
  } else {
    return false;
  }
}

node* BST::getNode(int const value, node* source) {
  if (source == nullptr || source->val == value) return source;

  if (source->val > value) {
    return getNode(value, source->left);
  } else {
    return getNode(value, source->right);
  }

  return nullptr;
}

int BST::getHeight(node* source) {
  if (source == nullptr) return -1;
  return 1 + std::max(getHeight(source->left), getHeight(source->right));
}

int BST::getDepth(int const Value, node* source) {
  int depth = 0;
  if (source == nullptr)
    return -1;
  else if (source->val == Value)
    return 0;
  else if (source->val > Value)
    depth = 1 + getDepth(Value, source->left);
  else
    depth = 1 + getDepth(Value, source->right);

  return depth == -1 ? -1 : depth + 1;
}

void BST::printPreOrder(node* source) {}

void BST::printInOrder(node* source) {}

void BST::printPostOrder(node* source) {}

bool isBST(node* root) {
  if (root == nullptr) return true;
  if ((root->left != nullptr && root->left->val >= root->val) ||
      (root->right != nullptr && root->right->val <= root->val))
    return false;
  else
    return isBST(root->left) && isBST(root->right);
}

node* invertTree(node* root) {  // leetcode 226
  if (root == nullptr) return nullptr;
  node* l = root->left;
  root->left = invertTree(root->right);
  //   root->left =
  return nullptr;
}

int main() {
  BST bst;
  return 0;
}
